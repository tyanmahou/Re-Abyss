#pragma once
#include <abyss/modules/Sound/Se/SeCaches.hpp>
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>

namespace abyss::Sound
{
    class SoundEffects
    {
    public:
        SoundEffects(ISoundBank* pSoundBank, Resource::Assets* pAssets = Resource::Assets::Norelease());

        /// <summary>
        /// 再生
        /// </summary>
        void play(const SoundLabel& label);

        void setVolume(double volume);
        void setVolume(double volume, const s3d::Duration& time);
    private:
        ISoundBank* m_pSoundBank;
        Resource::Assets* m_pAssets;
        SeCaches m_cache;
    };
}
