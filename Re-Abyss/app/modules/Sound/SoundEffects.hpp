#pragma once
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Sound
{
    class SoundEffects
    {
    public:
        SoundEffects(Resource::Assets* pAssets = Resource::Assets::Norelease());

        /// <summary>
        /// 再生
        /// </summary>
        /// <param name="path"></param>
        void play(const s3d::String& path);

        void setVolume(double volume);
        void setVolume(double volume, const s3d::Duration& time);
    private:
        s3d::Audio load(const s3d::String& path);
    private:
        Resource::Assets* m_pAssets;
        s3d::HashTable<s3d::FilePath, s3d::Audio> m_cache;
    };
}
