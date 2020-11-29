#include "ResourceManager.hpp"
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>
#include <abyss/utils/AudioSetting/AudioSettingGroup.hpp>
#include <Siv3D.hpp>
#include <S3DTiled.hpp>
namespace abyss
{
    class ResourceManager::Impl
    {
        s3d::HashTable<String, s3dTiled::TiledMap> m_tmxCache;
        s3d::HashTable<String, Texture> m_textureCache;
        s3d::HashTable<String, TexturePacker> m_texturePackerCache;
        s3d::HashTable<String, Audio> m_audioCache;
        s3d::HashTable<String, AudioSettingGroup> m_audioGroupCache;
        s3d::HashTable<String, PixelShader> m_psCache;
        s3d::HashTable<String, TOMLValue> m_tomlCache;
#if ABYSS_DEBUG
        bool m_isBuilded = false;
#else
        bool m_isBuilded = true;
#endif
    public:
        template<class Type, class ReadType = Type, class ... Args> 
        const Type& load(s3d::HashTable<String, Type>& cache, const s3d::FilePath& path, Args&&... args)
        {
            if (cache.find(path) != cache.end()) {
                return cache[path];
            }
            ReadType rc(FileUtil::FixResource(path, m_isBuilded), std::forward<Args>(args)...);
#if ABYSS_DEBUG
            if (!rc) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return cache[path] = rc;
        }

        s3dTiled::TiledMap loadTmx(const s3d::FilePath& path)
        {
            return this->load(m_tmxCache, path);
        }

        s3d::Texture loadTexture(const s3d::FilePath& path)
        {
            return this->load(m_textureCache, path);
        }
        TexturePacker loadTexturePacker(const s3d::FilePath& path)
        {
            return this->load(m_texturePackerCache, path);
        }
        Audio loadAudio(const s3d::FilePath& path)
        {
            if (m_audioCache.find(path) != m_audioCache.end()) {
                return m_audioCache[path];
            }
            Audio ret;
            auto fixPath = FileUtil::FixResource(path, m_isBuilded);
            if (FileUtil::Extension(fixPath) == U"aas") {
                AudioSettingReader reader;
                auto as = reader.load(fixPath);
                ret = this->loadAudio(as.path);
                as.apply(ret);
            } else {
                ret = Audio(fixPath);
            }

#if ABYSS_DEBUG
            if (!ret) {
                Debug::Log::PrintCache << U"Failed Load:" << path;
            }
#endif
            return m_audioCache[path] = ret;
        }
        AudioSettingGroup loadAudioSettingGroup(const s3d::FilePath& path)
        {
            return this->load<AudioSettingGroup>(m_audioGroupCache, path);
        }
        PixelShader loadPs(const s3d::FilePath& path)
        {
            return this->load<PixelShader>(m_psCache, path, Array<ConstantBufferBinding>{ { U"PSConstants2D", 0 } });
        }
        const s3d::TOMLValue& loadToml(const s3d::FilePath& path)
        {
            return this->load<TOMLValue, TOMLReader>(m_tomlCache, path);
        }

        void release()
        {
            m_tmxCache.clear();
            m_textureCache.clear();
            m_texturePackerCache.clear();
            m_psCache.clear();
            m_tomlCache.clear();
            m_audioCache.clear();
            m_audioGroupCache.clear();
        }

        void setIsBuilded(bool isBuilded)
        {
            m_isBuilded = isBuilded;
        }
    };

    ResourceManager::ResourceManager():
        m_pImpl(std::make_unique<Impl>())
    {
    }
    ResourceManager::~ResourceManager()
    {
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

    AudioSettingGroup ResourceManager::loadAudioSettingGroup(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudioSettingGroup(FileUtil::FixRelativePath(prefix + path));
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
        return Instance();
    }
}
