#include "Manager.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/Mrp/Mrp.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/commons/Resource/Preload/PreloadInfo.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace
{
    using namespace abyss::Resource::Preload;

    struct PreloadInfoEx : PreloadInfo
    {
        s3d::Array<s3d::String> preload;
    };
    PreloadInfoEx FromMrpGroup(const Mrp::MrpGroup &data)
    {
        PreloadInfoEx ret;
        for (const auto& [kind, path] : data) {
            if (kind == U"@") {
                ret.preload << path;
            } else if (kind == U"img") {
                if (FileSystem::Extension(path) == U"json") {
                    ret.texturePacker << path;
                } else {
                    ret.texture << path;
                }
            } else if (kind == U"tmx") {
                ret.tmx << path;
            } else if (kind == U"vs") {
                ret.vertexShader << path;
            } else if (kind == U"ps") {
                ret.pixelShader << path;
            } else if (kind == U"snd") {
                if (FileSystem::Extension(path) == U"aase") {
                    ret.audioSettingGroup << path;
                } else {
                    ret.audio << path;
                }
            } else if (kind == U"toml") {
                ret.toml << path;
            }
        }
        return ret;
    }

    s3d::Array<s3d::FilePath> GetPreloadFile()
    {
        s3d::Array<s3d::FilePath> ret;
#if ABYSS_NO_BUILD_RESOURCE
        for (auto& path : s3d::FileSystem::DirectoryContents(abyss::Path::PreloadPath)) {
            if (s3d::FileSystem::Extension(path) == U"mrp") {
                ret.push_back(s3d::FileSystem::RelativePath(path));
            }
        }
#else
        for (auto&& path : s3d::EnumResourceFiles()) {
            if (path.starts_with(U"PRELOADS")) {
                ret.push_back(path);
            }
        }
#endif
        return ret;
    }
}

namespace abyss::Resource::Preload
{
    class Manager::Impl
    {
    public:
        Impl()
        {
            for (const auto& path : GetPreloadFile()) {
                Mrp::Mrp mrp(FileUtil::FixPath(path));
                if (!mrp) {
                    continue;
                }
                for (const auto& [name, value] : mrp) {
#if ABYSS_DEBUG
                    if (m_prelaodInfos.contains(name)) {
                        Debug::LogWarn << U"Duplicated Load Preload Name: {}"_fmt(name);
                    }
#endif
                    m_prelaodInfos.emplace(name, FromMrpGroup(value));
                }
            }
        }
    public:
        PreloadInfo getInfo(const s3d::String& preloadName)
        {
            if (m_cache.contains(preloadName)) {
                return m_cache[preloadName];
            }
            // 先にインスタンス生成
            m_cache[preloadName] = PreloadInfo{};

            PreloadInfo ret{};
            const auto& other = m_prelaodInfos[preloadName];
            ret += other;
            for (const auto& p : other.preload) {
                ret += getInfo(p);
            }
            return m_cache[preloadName] = ret.unique();
        }
    private:
        HashTable<String, PreloadInfoEx> m_prelaodInfos;
        HashTable<String, PreloadInfo> m_cache;
    };
    PreloadInfo Manager::GetInfo(const s3d::String& preloadName)
    {
        return Instance()->m_pImpl->getInfo(preloadName);
    }
    Manager::Manager() :
        m_pImpl(std::make_unique<Impl>())
    {}
}
