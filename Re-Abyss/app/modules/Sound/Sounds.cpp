#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/Sound/MixBus.hpp>
#include <Siv3D.hpp>

namespace abyss::Sound
{
    Sounds::Sounds(SceneSound* pSceneSound):
        m_pSceneSound(pSceneSound)
    {
    }
    Sounds::~Sounds()
    {
    }
    void Sounds::play(const s3d::String& path, const s3d::Duration& sec)
    {
        bgm()->play(path, sec);
    }
    void Sounds::play(const SoundLabel& label, const s3d::Duration& sec)
    {
        bgm()->play(label, sec);
    }
    void Sounds::stop(const Duration& sec)
    {
        bgm()->stop(sec);
    }
    void Sounds::stash(const s3d::Duration& sec)
    {
        bgm()->stash(sec);
    }
    void Sounds::stashPop(const s3d::Duration& sec)
    {
        bgm()->stashPop(sec);
    }
    void Sounds::release()
    {
        bgm()->release();
    }
    const s3d::Optional<s3d::String>& Sounds::currentBgmPath() const
    {
        return bgm()->getCurrentPath();
    }
    void Sounds::setBgmVolume(double volume)
    {
        bgm()->setVolume(volume);
    }
    void Sounds::setBgmVolume(double volume, const s3d::Duration& time)
    {
        bgm()->setVolume(volume, time);
    }
    void Sounds::playSe(const s3d::String& path)
    {
        se()->play(path);
    }
    void Sounds::setMasterVolume(double volume)
    {
        GlobalAudio::SetVolume(volume);
    }
    void Sounds::setMasterVolume(double volume, const s3d::Duration& time)
    {
        GlobalAudio::FadeVolume(volume, time);
    }
    BackGroundMusic* Sounds::bgm() const
    {
        return m_pSceneSound->bgm();
    }
    SoundEffects* Sounds::se() const
    {
        return m_pSceneSound->se();
    }
}
