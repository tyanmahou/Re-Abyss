#include "ResourceManager.hpp"
#include <abyss/debugs/Log/Log.hpp>

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
    public:
        s3dTiled::TiledMap loadTmx(const s3d::FilePath& path)
        {
            if (m_tmxCache.find(path) != m_tmxCache.end()) {
                return m_tmxCache[path];
            }
            auto tmx = s3dTiled::TiledMap(path);
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
            auto tex = s3d::Texture(path);
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
            auto tex = TexturePacker(path);
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
            auto audio = Audio(path);
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
            auto ps = s3d::PixelShader(path, { { U"PSConstants2D", 0 } });
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
            auto toml = TOMLReader(path);
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
        return m_pImpl->loadTmx(prefix + path);
    }
    s3d::Texture ResourceManager::loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexture(prefix + path);
    }

    TexturePacker ResourceManager::loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexturePacker(prefix + path);
    }

    s3d::Audio ResourceManager::loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudio(prefix + path);
    }

    s3d::PixelShader ResourceManager::loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadPs(prefix + path);
    }

    const s3d::TOMLValue& ResourceManager::loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadToml(prefix + path);
    }

    void ResourceManager::release() const
    {
        return m_pImpl->release();
    }

    ResourceManager* ResourceManager::Main()
    {
        return s_main;
    }
}
