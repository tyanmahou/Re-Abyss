#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Audio.hpp>
#include <Siv3D/PixelShader.hpp>
#include <Siv3D/String.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace s3dTiled
{
    class TiledMap;
}

namespace abyss
{
    class AudioSettingGroup;
}
namespace abyss::Resource
{
    class AssetLoadProxy;

    class Assets : s3d::Uncopyable
    {
        class Impl;
        std::unique_ptr<Impl> m_pImpl;


        Assets();
    public:
        ~Assets();

        AssetLoadProxy load(const s3d::FilePath& path) const;
        AssetLoadProxy load(const s3d::FilePath& path, const s3d::String& prefix) const;

        const s3dTiled::TiledMap& loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::MapPath) const;
        const s3d::Texture& loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        const TexturePacker& loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        s3d::Audio loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;
        const AudioSettingGroup& loadAudioSettingGroup(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;

        const s3d::PixelShader& loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ShaderPath) const;

        const s3d::TOMLValue& loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ParamPath) const;

        template<class Entity>
        Entity loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ParamPath) const
        {
            return TOMLBind<Entity>{}(this->loadToml(path, prefix));
        }

        void release() const;

        void free();
#if ABYSS_DEBUG
        /// <summary>
        /// ロード入ると警告入れます
        /// </summary>
        /// <param name="isWarnMode"></param>
        void setWarnMode(bool isWarnMode) const;
#endif
    public:
        /// <summary>
        /// メインアセット
        /// </summary>
        /// <returns></returns>
        static Assets* Main();
        /// <summary>
        /// リリースしないアセット
        /// </summary>
        /// <returns></returns>
        static Assets* Norelease();
    };

    /// <summary>
    /// アセットロードプロキシ
    /// </summary>
    class AssetLoadProxy
    {
    public:
        AssetLoadProxy(const Assets& asset, const s3d::FilePath& path, const s3d::Optional<s3d::FilePath>& prefix);

        operator const s3dTiled::TiledMap& () const;
        operator const s3d::Texture& () const;
        operator const TexturePacker& () const;
        operator s3d::Audio () const;
        operator const AudioSettingGroup& () const;
        operator const s3d::PixelShader& () const;
        operator const s3d::TOMLValue& () const;
    private:
        const Assets& m_asset;
        s3d::FilePath m_path;
        s3d::Optional<s3d::FilePath> m_prefix;
    };
}