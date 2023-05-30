#include <abyss/modules/Sound/Se/SeCaches.hpp>

namespace abyss::Sound
{
    s3d::Audio SeCaches::load(Resource::Assets* pAssets, const s3d::String& path)
    {
        if (auto it = m_cache.find(path); it != m_cache.end()) {
            return it->second;
        }
        return m_cache[path] = pAssets->loadAudio(path, Path::Root);
    }
}
