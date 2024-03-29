#include <abyss/modules/Sound/Bgm/BackGroundMusic.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/modules/Sound/MixBus.hpp>

namespace abyss::Sound
{
    BackGroundMusic::BackGroundMusic(ISoundBank* pSoundBank, Resource::Assets* pAssets):
        m_pSoundBank(pSoundBank),
        m_pAssets(pAssets)
    {
    }
    void BackGroundMusic::play(const SoundLabel& label, const s3d::Duration& sec)
    {
        if (m_currentLabel == label) {
            if (!m_current.isPlaying()) {
                m_current.play(MixBusKind::Bgm, sec);
            }
            return;
        }
        m_currentLabel = label;
        m_prev = m_current;

        // Bgm はストリーミング再生
        m_current = m_pAssets->loadAudio(s3d::Audio::Stream, m_pSoundBank->setting(label));

        if (m_prev.isPlaying()) {
            m_prev.stop(sec);
        }
        m_current.setVolume(0.6);
        m_current.play(MixBusKind::Bgm, sec);
    }
    void BackGroundMusic::stop(const s3d::Duration & sec)
    {
        m_currentLabel = s3d::none;

        if (m_current.isPlaying()) {
            m_current.stop(sec);
        }
    }
    void BackGroundMusic::release()
    {
        m_current.release();
        m_prev.release();

        {
            std::stack<SoundLabel> empty{};
            m_stash.swap(empty);
        }
    }
    void BackGroundMusic::stash(const s3d::Duration& sec)
    {
        if (m_currentLabel) {
            m_stash.push(*m_currentLabel);
        }
        this->stop(sec);
    }
    void BackGroundMusic::stashPop(const s3d::Duration& sec)
    {
        if (!m_stash.empty()) {
            this->play(m_stash.top(), sec);
            m_stash.pop();
        }
    }
    void BackGroundMusic::setVolume(double volume)
    {
        GlobalAudio::BusSetVolume(MixBusKind::Bgm, volume);
    }
    void BackGroundMusic::setVolume(double volume, const s3d::Duration& time)
    {
        GlobalAudio::BusFadeVolume(MixBusKind::Bgm, volume, time);
    }
}
