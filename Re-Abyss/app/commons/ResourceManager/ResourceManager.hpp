#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace s3dTiled
{
    class TiledMap;
}

namespace abyss
{
    class AudioGroup;

    namespace Path
    {
        inline static s3d::FilePath Root = U"";
        inline static s3d::FilePath ResourcePath = U"resources/";
        inline static s3d::FilePath ImagePath = ResourcePath + U"images/";
        inline static s3d::FilePath MapPath = ResourcePath + U"maps/";
        inline static s3d::FilePath ParamPath = ResourcePath + U"params/";
        inline static s3d::FilePath ShaderPath = ResourcePath + U"shaders/";
        inline static s3d::FilePath SoundPath = ResourcePath + U"sounds/";
    }

    class ResourceManager
    {
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

    public:
        ResourceManager();
        ~ResourceManager();

        s3dTiled::TiledMap loadTmx(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::MapPath);
        s3d::Texture loadTexture(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        TexturePacker loadTexturePacker(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ImagePath) const;
        s3d::Audio loadAudio(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;
        AudioGroup loadAudioGroup(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::SoundPath) const;

        s3d::PixelShader loadPs(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ShaderPath) const;

        const s3d::TOMLValue& loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ParamPath) const;

        template<class Entity>
        Entity loadToml(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::ParamPath) const
        {
            return TOMLBind<Entity>{}(this->loadToml(path, prefix));
        }

        void release() const;


        void setIsBuilded(bool isBuilded) const;
    private:
        inline static ResourceManager* s_main = nullptr;
    public:
        static ResourceManager* Main();
    };
}