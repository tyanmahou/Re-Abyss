#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Sound/MixBus.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    Sound::Sound(SceneSound* pSceneSound):
        m_pSceneSound(pSceneSound)
    {
    }
    Sound::~Sound()
    {
    }
    void Sound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        m_pSceneSound->bgm.play(path, sec);
    }
    void Sound::stop(const Duration& sec)
    {
        m_pSceneSound->bgm.stop(sec);
    }
    void Sound::stash(const s3d::Duration& sec)
    {
        m_pSceneSound->bgm.stash(sec);
    }
    void Sound::stashPop(const s3d::Duration& sec)
    {
        m_pSceneSound->bgm.stashPop(sec);
    }
    void Sound::release()
    {
        m_pSceneSound->bgm.release();
    }
    const s3d::Optional<s3d::String>& Sound::currentBgmPath() const
    {
        return m_pSceneSound->bgm.getCurrentPath();
    }
    void Sound::setBgmVolume(double volume)
    {
        m_pSceneSound->bgm.setVolume(volume);
    }
    void Sound::setBgmVolume(double volume, const s3d::Duration& time)
    {
        m_pSceneSound->bgm.setVolume(volume, time);
    }
    void Sound::playSe(const s3d::String& path)
    {
        m_pSceneSound->se.play(path);
    }
    void Sound::setMasterVolume(double volume)
    {
        GlobalAudio::SetVolume(volume);
    }
    void Sound::setMasterVolume(double volume, const s3d::Duration& time)
    {
        GlobalAudio::FadeVolume(volume, time);
    }
}
