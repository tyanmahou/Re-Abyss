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
    struct AssetLoadTraits<s3d::PixelShader>
    {
        s3d::PixelShader load(const s3d::FilePath& path) const
        {
            return HLSL{ path, U"PS" };
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
        s3d::HashTable<String, Wave> m_audioCache;
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
                Debug::LogLoad << U"Failed Load:" << fixPath;
            } else if (m_isWarnMode) {
                Debug::LogLoad << U"Load: " << fixPath;
            }
#endif
            return cache[fixPath] = rc;
        }

        const s3dTiled::TiledMap& loadTmx(const s3d::FilePath& path)
        {
            return this->load(m_tmxCache, path);
        }

        const s3d::Texture& loadTexture(const s3d::FilePath& path)
        {
            return this->load(m_textureCache, path);
        }
        const TexturePacker& loadTexturePacker(const s3d::FilePath& path)
        {
            return this->load(m_texturePackerCache, path);
        }
        const Wave& loadWave(const s3d::FilePath& path)
        {
            return this->load(m_audioCache, path);
        }
        s3d::Audio loadAudio(const AudioSetting& as)
        {
            const Wave& wave = this->loadWave(as.path);
            return as.apply(wave);
        }
        s3d::Audio loadAudio(const s3d::FilePath& path)
        {
            if (FileUtil::Extension(path) == U"aas") {
                AudioSettingReader reader;
                auto as = reader.load(path);
                return this->loadAudio(as);
            } else {
                return s3d::Audio(this->loadWave(path));
            }
        }
        const AudioSettingGroup& loadAudioSettingGroup(const s3d::FilePath& path)
        {
            return this->load<AudioSettingGroup>(m_audioGroupCache, path);
        }
        const PixelShader& loadPs(const s3d::FilePath& path)
        {
            return this->load<PixelShader>(m_psCache, path);
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
    AssetLoadProxy Assets::load(const s3d::FilePath& path) const
    {
        return AssetLoadProxy(*this, path, s3d::none);
    }
    AssetLoadProxy Assets::load(const s3d::FilePath& path, const s3d::String& prefix) const
    {
        return AssetLoadProxy(*this, path, prefix);
    }
    const s3dTiled::TiledMap& Assets::loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTmx(prefix + path);
    }
    const s3d::Texture& Assets::loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexture(prefix + path);
    }

    const TexturePacker& Assets::loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadTexturePacker(prefix + path);
    }

    s3d::Audio Assets::loadAudio(const AudioSetting& as) const
    {
        return m_pImpl->loadAudio(as);
    }

    s3d::Audio Assets::loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudio(prefix + path);
    }

    const AudioSettingGroup& Assets::loadAudioSettingGroup(const s3d::FilePath& path, const s3d::FilePath& prefix) const
    {
        return m_pImpl->loadAudioSettingGroup(prefix + path);
    }

    const s3d::PixelShader& Assets::loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix) const
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

    // -------------------------------------------------

    AssetLoadProxy::AssetLoadProxy(const Assets& asset, const s3d::FilePath& path, const s3d::Optional<s3d::FilePath>& prefix) :
        m_asset(asset),
        m_path(path),
        m_prefix(prefix)
    {}
    AssetLoadProxy::operator const s3dTiled::TiledMap& () const
    {
        if (m_prefix) {
            return m_asset.loadTmx(m_path, *m_prefix);
        }
        return m_asset.loadTmx(m_path);
    }
    AssetLoadProxy::operator const s3d::Texture& () const
    {
        if (m_prefix) {
            return m_asset.loadTexture(m_path, *m_prefix);
        }
        return m_asset.loadTexture(m_path);
    }
    AssetLoadProxy::operator const TexturePacker& () const
    {
        if (m_prefix) {
            return m_asset.loadTexturePacker(m_path, *m_prefix);
        }
        return m_asset.loadTexturePacker(m_path);
    }
    AssetLoadProxy::operator s3d::Audio () const
    {
        if (m_prefix) {
            return m_asset.loadAudio(m_path, *m_prefix);
        }
        return m_asset.loadAudio(m_path);
    }
    AssetLoadProxy::operator const AudioSettingGroup& () const
    {
        if (m_prefix) {
            return m_asset.loadAudioSettingGroup(m_path, *m_prefix);
        }
        return m_asset.loadAudioSettingGroup(m_path);
    }
    AssetLoadProxy::operator const s3d::PixelShader& () const
    {
        if (m_prefix) {
            return m_asset.loadPs(m_path, *m_prefix);
        }
        return m_asset.loadPs(m_path);
    }
    AssetLoadProxy::operator const s3d::TOMLValue& () const
    {
        if (m_prefix) {
            return m_asset.loadToml(m_path, *m_prefix);
        }
        return m_asset.loadToml(m_path);
    }
}
