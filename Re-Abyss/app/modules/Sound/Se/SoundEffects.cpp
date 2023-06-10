#include <abyss/modules/Sound/Se/SoundEffects.hpp>
#include <abyss/modules/Sound/MixBus.hpp>

namespace abyss::Sound
{
    SoundEffects::SoundEffects(ISoundBank* pSoundBank, Resource::Assets* pAssets):
        m_pSoundBank(pSoundBank),
        m_pAssets(pAssets)
    {
    }
    void SoundEffects::play(const SoundLabel& label)
    {
        Audio audio = m_cache.load(m_pAssets, m_pSoundBank, label);
        audio.playOneShot(MixBusKind::Se, 0.4);
    }
    void SoundEffects::setVolume(double volume)
    {
        GlobalAudio::BusSetVolume(MixBusKind::Se, volume);
    }
    void SoundEffects::setVolume(double volume, const s3d::Duration& time)
    {
        GlobalAudio::BusFadeVolume(MixBusKind::Se, volume, time);
    }
}
