#include "Sound.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    Sound::~Sound()
    {
    }
    void Sound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        m_bgm.play(path, sec);
    }
    void Sound::stop(const Duration& sec)
    {
        m_bgm.stop(sec);
    }
    void Sound::release()
    {
        m_bgm.release();
    }
    const s3d::Optional<s3d::String>& Sound::currentBgmPath() const
    {
        return m_bgm.getCurrentPath();
    }
}
