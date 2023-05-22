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
}
