#include <abyss/modules/Sound/SoundEffects.hpp>
#include <abyss/modules/Sound/MixBus.hpp>

namespace abyss
{
    SoundEffects::SoundEffects(Resource::Assets* pAssets):
        m_pAssets(pAssets)
    {
    }
    void SoundEffects::play(const s3d::String& path)
    {
        auto audio = m_pAssets->loadAudio(path, Path::Root);
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
