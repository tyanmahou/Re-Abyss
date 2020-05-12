#include "ResourceManager.hpp"
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

#include <Siv3D.hpp>
#include<S3DTiled.hpp>

namespace abyss
{
    class ResourceManager::Impl
    {
        s3d::HashTable<String, s3dTiled::TiledMap> m_tmxCache;
        s3d::HashTable<String, Texture> m_textureCache;
        s3d::HashTable<String, TexturePacker> m_texturePackerCache;
        s3d::HashTable<String, Audio> m_audioCache;
        s3d::HashTable<String, PixelShader> m_psCache;
        s3d::HashTable<String, TOMLValue> m_tomlCache;

        bool m_isBuilded = true;
    public:

        s3dTiled::TiledMap loadTmx(const s3d::FilePath& path)
        {
            if (m_tmxCache.find(path) != m_tmxCache.end()) {
                return m_tmxCache[path];
            }
            auto tmx = s3dTiled::TiledMap(FileUtil::FixResource(path, m_isBuilded));
#if ABYSS_DEBUG
            if (!tmx) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_tmxCache[path] = tmx;
        }

        s3d::Texture loadTexture(const s3d::FilePath& path)
        {
            if (m_textureCache.find(path) != m_textureCache.end()) {
                return m_textureCache[path];
            }
            auto tex = s3d::Texture(FileUtil::FixResource(path, m_isBuilded));
#if ABYSS_DEBUG
            if (!tex) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_textureCache[path] = tex;
        }
        TexturePacker loadTexturePacker(const s3d::FilePath& path)
        {
            if (m_texturePackerCache.find(path) != m_texturePackerCache.end()) {
                return m_texturePackerCache[path];
            }
            auto tex = TexturePacker(FileUtil::FixResource(path, m_isBuilded));
#if ABYSS_DEBUG
            if (!tex) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_texturePackerCache[path] = tex;
        }
        Audio loadAudio(const s3d::FilePath& path)
        {
            if (m_audioCache.find(path) != m_audioCache.end()) {
                return m_audioCache[path];
            }
            auto audio = Audio(FileUtil::FixResource(path, m_isBuilded));
#if ABYSS_DEBUG
            if (!audio) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_audioCache[path] = audio;
        }
        PixelShader loadPs(const s3d::FilePath& path)
        {
            if (m_psCache.find(path) != m_psCache.end()) {
                return m_psCache[path];
            }
            auto ps = s3d::PixelShader(FileUtil::FixResource(path, m_isBuilded), { { U"PSConstants2D", 0 } });
#if ABYSS_DEBUG
            if (!ps) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_psCache[path] = ps;
        }
        const s3d::TOMLValue& loadToml(const s3d::FilePath& path)
        {
            if (m_tomlCache.find(path) != m_tomlCache.end()) {
                return m_tomlCache[path];
            }
            auto toml = TOMLReader(FileUtil::FixResource(path, m_isBuilded));
#if ABYSS_DEBUG
            if (!toml) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_tomlCache[path] = toml;
        }

        void release()
        {
            m_tmxCache.clear();
            m_textureCache.clear();
            m_texturePackerCache.clear();
            m_psCache.clear();
            m_tomlCache.clear();
            m_audioCache.clear();
        }

        void setIsBuilded(bool isBuilded)
        {
            m_isBuilded = isBuilded;
        }
    };

    ResourceManager::ResourceManager():
        m_pImpl(std::make_unique<Impl>())
    {
        s_main = this;
    }
    ResourceManager::~ResourceManager()
    {
        if (s_main == this) {
            s_main = nullptr;
        }
    }
    s3dTiled::TiledMap ResourceManager::loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix)
    {
        return m_pImpl->loadTmx(FileUtil::FixRelativePath(prefix + path));
    }
    s3d::Texture ResourceManager::loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexture(FileUtil::FixRelativePath(prefix + path));
    }

    TexturePacker ResourceManager::loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexturePacker(FileUtil::FixRelativePath(prefix + path));
    }

    s3d::Audio ResourceManager::loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudio(FileUtil::FixRelativePath(prefix + path));
    }

    s3d::PixelShader ResourceManager::loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadPs(FileUtil::FixRelativePath(prefix + path));
    }

    const s3d::TOMLValue& ResourceManager::loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadToml(FileUtil::FixRelativePath(prefix + path));
    }

    void ResourceManager::release() const
    {
        return m_pImpl->release();
    }

    void ResourceManager::setIsBuilded(bool isBuilded) const
    {
        m_pImpl->setIsBuilded(isBuilded);
    }

    ResourceManager* ResourceManager::Main()
    {
        return s_main;
    }
}
