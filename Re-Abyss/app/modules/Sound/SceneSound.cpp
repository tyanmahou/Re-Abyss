#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss
{
    SceneSound::SceneSound(Resource::Assets* pAssets):
        m_bgm(pAssets),
        m_se(pAssets)
    {
    }
}
