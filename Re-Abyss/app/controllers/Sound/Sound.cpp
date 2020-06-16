#include "Sound.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

namespace abyss
{
    Sound::~Sound()
    {
    }
    void Sound::play(const s3d::String& path, const s3d::Duration& sec)
    {
        m_currentPath = path;
        auto next = ResourceManager::Main()->loadAudio(path, U"");
        if (m_current == next) {
            if (!m_current.isPlaying()) {
                m_current.play(sec);
            }
            return;
        }
        m_prev = m_current;
        m_current = next;
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
    void Sound::release() const
    {
        // リソースには残るので停止だけする
        if (m_prev.isPlaying()) {
            m_prev.stop();
        }
        if (m_current.isPlaying()) {
            m_current.stop();
        }
    }
}
