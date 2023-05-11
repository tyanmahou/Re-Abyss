#include <abyss/modules/Sound/Sound.hpp>
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
        m_pSceneSound->play(path, sec);
    }
    void Sound::stop(const Duration& sec)
    {
        m_pSceneSound->stop(sec);
    }
    void Sound::stash(const s3d::Duration& sec)
    {
        m_pSceneSound->stash(sec);
    }
    void Sound::stashPop(const s3d::Duration& sec)
    {
        m_pSceneSound->stashPop(sec);
    }
    void Sound::release()
    {
        m_pSceneSound->release();
    }
    const s3d::Optional<s3d::String>& Sound::currentBgmPath() const
    {
        return m_pSceneSound->currentBgmPath();
    }
}
