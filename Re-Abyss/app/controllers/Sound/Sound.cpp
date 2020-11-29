#include "Sound.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

namespace abyss
{
    Sound::~Sound()
    {
    }
    void Sound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        m_currentPath = path;
        auto next = Resource::Assets::Main()->loadAudio(path, U"");
        if (m_currentId == next.id()) {
            if (!m_current.isPlaying()) {
                m_current.play(sec);
            }
            return;
        }
        m_prev = m_current;

        m_currentId = next.id();
        m_current = Audio(next.getWave());
        if (auto loop = next.getLoop()) {
            m_current.setLoop(loop->beginPos, loop->endPos);
        }

        if (m_prev.isPlaying()) {
            m_prev.stop(sec);
        }
        m_current.setVolume(0.6);
        m_current.play(sec);
    }
    void Sound::stop(const Duration& sec)
    {
        m_currentPath = s3d::none;
        m_currentId = Audio::IDType();

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
