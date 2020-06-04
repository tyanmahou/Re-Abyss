#pragma once
#include <Siv3D/TextureRegion.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class DecorGraphicsManager
    {
    public:
        class Anime
        {
            struct Frame
            {
                s3d::uint32 gId;
                double duration;
            };
            s3d::Array<Frame> m_frames;
            double m_maxDuration = 0;
        public:
            void add(s3d::uint32 gId, double duration);
            s3d::uint32 getGId(double time) const;
            bool isEmpty()const;
        };
        struct Info
        {
            s3d::String filePath;
            s3d::Vec2 offset;
            s3d::Vec2 size;
        };
    private:
        s3d::HashTable<s3d::uint32, s3d::TextureRegion> m_textures;
        s3d::HashTable<s3d::uint32, Info> m_infos;
        s3d::HashTable<s3d::uint32, Anime> m_animes;
    public:
        DecorGraphicsManager() = default;
        void addInfo(s3d::uint32 gId, const Info& info);
        void addInfo(s3d::uint32 gId, Info&& info);
        void addAnime(s3d::uint32 gId, const Anime& anime);
        void addAnime(s3d::uint32 gId, Anime&& anime);
        s3d::TextureRegion getTexture(s3d::uint32 gId, double time);
    };
}