#include <abyss/debugs/HotReload/HotReloadUtil.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/scenes/Scene/Boot/Initializer.hpp>

namespace abyss::Debug
{
    using namespace abyss::Resource;

    void HotReloadUtil::ReloadAssetCommon(const Debug::FileChanges& changes)
    {
        if (changes.empty()) {
            return;
        }
        // TODO changesで必要なものだけリロード
        Assets::Main()->release();
        Assets::Norelease()->release();
        Assets::Temporray()->release();
        Scene::Boot::Initializer::LoadAsset();
    }
}
#endif
