#include "Assets.hpp"
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>
#include <abyss/utils/AudioSetting/AudioSettingGroup.hpp>
#include <Siv3D.hpp>
#include <S3DTiled.hpp>

namespace
{
    using namespace abyss;

    template<class Type>
    struct AssetLoadTraits
    {
        template<class... Args>
        Type load(const s3d::FilePath& path, Args&&... args) const
        {
            return Type(path, std::forward<Args>(args)...);
        }
    };

    template<>
    struct AssetLoadTraits<s3d::Audio>
    {
        template<class Callback>
        s3d::Audio load(const s3d::FilePath& path, const Callback& callback) const
        {
            if (FileUtil::Extension(path) == U"aas") {
                AudioSettingReader reader;
                auto as = reader.load(path);
                Audio ret = callback(as.path);
                as.apply(ret);
                return ret;
            } else {
                return s3d::Audio(path);
            }
        }
    };
}
namespace abyss::Resource
{
    class Assets::Impl
    {
        s3d::HashTable<String, s3dTiled::TiledMap> m_tmxCache;
        s3d::HashTable<String, Texture> m_textureCache;
        s3d::HashTable<String, TexturePacker> m_texturePackerCache;
        s3d::HashTable<String, Audio> m_audioCache;
        s3d::HashTable<String, AudioSettingGroup> m_audioGroupCache;
        s3d::HashTable<String, PixelShader> m_psCache;
        s3d::HashTable<String, TOMLValue> m_tomlCache;
#if ABYSS_NO_BUILD_RESOURCE
        bool m_isBuilded = false;
#else
        bool m_isBuilded = true;
#endif
#if ABYSS_DEBUG
        bool m_isWarnMode = false;
#endif
    public:
        template<class Type, class ReadType = Type, class ... Args> 
        const Type& load(s3d::HashTable<String, Type>& cache, const s3d::FilePath& path, Args&&... args)
        {
            const auto fixPath = FileUtil::FixPath(path, m_isBuilded);
            if (cache.find(fixPath) != cache.end()) {
                return cache[fixPath];
            }
            ReadType rc = AssetLoadTraits<ReadType>{}.load(fixPath, std::forward<Args>(args)...);
#if ABYSS_DEBUG
            if (!rc) {
                Debug::Log::PrintCache << U"Failed Load:" << fixPath;
            } else if (m_isWarnMode) {
                Debug::Log::PrintCache << U"Load: " << fixPath;
            }
#endif
            return cache[fixPath] = rc;
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
            return this->load(m_audioCache, path, [this](const s3d::FilePath& callbackPath) {
                return this->loadAudio(callbackPath);
            });
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
#if ABYSS_DEBUG
        void setWarnMode(bool isWarnMode)
        {
            m_isWarnMode = isWarnMode;
        }
#endif
    };

    Assets::Assets():
        m_pImpl(std::make_unique<Impl>())
    {
    }
    Assets::~Assets()
    {
    }
    s3dTiled::TiledMap Assets::loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTmx(prefix + path);
    }
    s3d::Texture Assets::loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexture(prefix + path);
    }

    TexturePacker Assets::loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexturePacker(prefix + path);
    }

    s3d::Audio Assets::loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudio(prefix + path);
    }

    AudioSettingGroup Assets::loadAudioSettingGroup(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudioSettingGroup(prefix + path);
    }

    s3d::PixelShader Assets::loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadPs(prefix + path);
    }

    const s3d::TOMLValue& Assets::loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadToml(prefix + path);
    }

    void Assets::release() const
    {
        return m_pImpl->release();
    }

    void Assets::free()
    {
        m_pImpl.release();
    }

#if ABYSS_DEBUG
    void Assets::setWarnMode(bool isWarnMode) const
    {
        m_pImpl->setWarnMode(isWarnMode);
    }
#endif
    Assets* Assets::Main()
    {
        static Assets instance;
        return &instance;
    }
    Assets* Assets::Norelease()
    {
        static Assets instance;
        return &instance;
    }
}
