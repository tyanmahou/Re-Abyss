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
        Resource::Assets* m_pAssets;
    };
}
