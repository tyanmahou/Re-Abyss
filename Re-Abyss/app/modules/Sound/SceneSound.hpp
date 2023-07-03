#pragma once
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>
#include <abyss/modules/Sound/Bgm/BackGroundMusic.hpp>
#include <abyss/modules/Sound/Se/SoundEffects.hpp>

namespace abyss::Sound
{
    class SceneSound
    {
    public:
        SceneSound(std::shared_ptr<ISoundBank> pSoundBank, Resource::Assets* pAssets = Resource::Assets::NoRelease());

        BackGroundMusic* bgm()
        {
            return &m_bgm;
        }
        SoundEffects* se()
        {
            return &m_se;
        }
        AudioSetting setting(const SoundLabel& label) const;
        s3d::Audio load(const SoundLabel& label, Resource::Assets* pAssets) const;
    private:
        std::shared_ptr<ISoundBank> m_soundbank;
        BackGroundMusic m_bgm;
        SoundEffects m_se;
    };
}
