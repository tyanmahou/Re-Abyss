#include "Sound.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

namespace abyss
{
    Sound::~Sound()
    {
    }
    void Sound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        const auto fixPath = FileUtil::FixRelativePath(path);
        if (m_currentPath == fixPath) {
            if (!m_current.isPlaying()) {
                m_current.play(sec);
            }
            return;
        }
        m_currentPath = fixPath;
        m_prev = m_current;

        m_current = Resource::Assets::Main()->load(fixPath, U"");

        if (m_prev.isPlaying()) {
            m_prev.stop(sec);
        }
        m_current.setVolume(0.6);
        m_current.play(sec);
    }
    void Sound::stop(const Duration& sec)
    {
        m_currentPath = s3d::none;

        if (m_current.isPlaying()) {
            m_current.stop(sec);
        }
    }
    void Sound::release()
    {
        m_current.release();
        m_prev.release();
    }
}
