#include <abyss/modules/Sound/Se/SeCaches.hpp>

namespace abyss::Sound
{
    s3d::Audio SeCaches::load(Resource::Assets* pAssets, ISoundBank* pSoundBank, const SoundLabel& label)
    {
        if (auto it = m_cache.find(label); it != m_cache.end()) {
            return it->second;
        }
        return m_cache[label] = pAssets->loadAudio(pSoundBank->setting(label));
    }
}
