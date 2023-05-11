#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss
{
    void SceneSound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        m_bgm.play(path, sec);
    }
    void SceneSound::stop(const s3d::Duration& sec)
    {
        m_bgm.stop(sec);
    }
    void SceneSound::stash(const s3d::Duration& sec)
    {
        m_bgm.stash(sec);
    }
    void SceneSound::stashPop(const s3d::Duration& sec)
    {
        m_bgm.stashPop(sec);
    }
    void SceneSound::release()
    {
        m_bgm.release();
    }
    const s3d::Optional<s3d::String>& SceneSound::currentBgmPath() const
    {
        return m_bgm.getCurrentPath();
    }
}
