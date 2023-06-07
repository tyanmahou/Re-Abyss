#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss::Sound
{
    SceneSound::SceneSound(std::shared_ptr<ISoundBank> pSoundBank, Resource::Assets* pAssets):
        m_soundbank(pSoundBank),
        m_bgm(pSoundBank.get(), pAssets),
        m_se(pSoundBank.get(), pAssets)
    {
    }
}
