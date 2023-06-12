#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss::Sound
{
    SceneSound::SceneSound(std::shared_ptr<ISoundBank> pSoundBank, Resource::Assets* pAssets):
        m_soundbank(pSoundBank),
        m_bgm(pSoundBank.get(), pAssets),
        m_se(pSoundBank.get(), pAssets)
    {
    }
    AudioSetting SceneSound::setting(const SoundLabel& label) const
    {
        return m_soundbank->setting(label);
    }
    s3d::Audio SceneSound::load(const SoundLabel& label, Resource::Assets* pAssets) const
    {
        return pAssets->loadAudio(setting(label));
    }
}
