#pragma once
#include <abyss/modules/Sound/BackGroundMusic.hpp>
#include <abyss/modules/Sound/SoundEffects.hpp>

namespace abyss::Sound
{
    class SceneSound
    {
    public:
        SceneSound(Resource::Assets* pAssets = Resource::Assets::Norelease());

        BackGroundMusic* bgm()
        {
            return &m_bgm;
        }
        SoundEffects* se()
        {
            return &m_se;
        }
    private:
        BackGroundMusic m_bgm;
        SoundEffects m_se;
    };
}
