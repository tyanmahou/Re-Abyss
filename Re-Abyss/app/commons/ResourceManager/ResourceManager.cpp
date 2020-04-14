#include "ResourceManager.hpp"
#include <abyss/debugs/DebugLog/DebugLog.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    class ResourceManager::Impl
    {
        s3d::HashTable<String, Texture> m_textureCache;
        s3d::HashTable<String, TexturePacker> m_texturePackerCache;
        s3d::HashTable<String, PixelShader> m_psCache;
        s3d::HashTable<String, TOMLValue> m_tomlCache;
    public:
        s3d::Texture loadTexture(const s3d::FilePath& path)
        {
            if (m_textureCache.find(path) != m_textureCache.end()) {
                return m_textureCache[path];
            }
            auto tex = s3d::Texture(path);
#if ABYSS_DEBUG
            if (!tex) {
                DebugLog::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_textureCache[path] = tex;
        }
        TexturePacker loadTexturePacker(const s3d::FilePath& path)
        {
            if (m_texturePackerCache.find(path) != m_texturePackerCache.end()) {
                return m_texturePackerCache[path];
            }
            auto tex = TexturePacker(path);
#if ABYSS_DEBUG
            if (!tex) {
                DebugLog::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_texturePackerCache[path] = tex;
        }
        PixelShader loadPs(const s3d::FilePath& path)
        {
            if (m_psCache.find(path) != m_psCache.end()) {
                return m_psCache[path];
            }
            auto ps = s3d::PixelShader(path, { { U"PSConstants2D", 0 } });
#if ABYSS_DEBUG
            if (!ps) {
                DebugLog::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_psCache[path] = ps;
        }
        const s3d::TOMLValue& loadToml(const s3d::FilePath& path)
        {
            if (m_tomlCache.find(path) != m_tomlCache.end()) {
                return m_tomlCache[path];
            }
            auto toml = TOMLReader(path);
#if ABYSS_DEBUG
            if (!toml) {
                DebugLog::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_tomlCache[path] = toml;
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
    s3d::Texture ResourceManager::loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexture(prefix + path);
    }

    TexturePacker ResourceManager::loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexturePacker(prefix + path);
    }

    s3d::PixelShader ResourceManager::loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadPs(prefix + path);
    }

    ResourceManager* ResourceManager::Main()
    {
        return s_main;
    }

    const s3d::TOMLValue& ResourceManager::loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadToml(prefix + path);
    }
}
