#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
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

    class Assets : s3d::Uncopyable
    {
        class Impl;
        std::unique_ptr<Impl> m_pImpl;


        Assets();
    public:
        ~Assets();

        s3dTiled::TiledMap loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::MapPath) const;
        s3d::Texture loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        TexturePacker loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        s3d::Audio loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;
        AudioSettingGroup loadAudioSettingGroup(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;

        s3d::PixelShader loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ShaderPath) const;

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
}