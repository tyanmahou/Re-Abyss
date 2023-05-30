#include <abyss/modules/Sound/Se/SoundEffects.hpp>
#include <abyss/modules/Sound/MixBus.hpp>

namespace abyss::Sound
{
    SoundEffects::SoundEffects(Resource::Assets* pAssets):
        m_pAssets(pAssets)
    {
    }
    void SoundEffects::play(const s3d::String& path)
    {
        Audio audio = load(path);
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
    s3d::Audio SoundEffects::load(const s3d::String& path)
    {
        if (auto it = m_cache.find(path); it != m_cache.end()) {
            return it->second;
        }
        return m_cache[path] = m_pAssets->loadAudio(path, Path::Root);
    }
}
