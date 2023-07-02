#include <abyss/debugs/HotReload/HotReloadUtil.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/scenes/Scene/Boot/Initializer.hpp>

namespace abyss::Debug
{
    using namespace abyss::Resource;

    void HotReloadUtil::ReloadAssetCommon(const s3d::Optional<s3d::Array<s3d::FileChange>>& changes)
    {
        // TODO changesで必要なものだけリロード
        Assets::Main()->release();
        Assets::Norelease()->release();
        Assets::Temporray()->release();
        Scene::Boot::Initializer::LoadAsset();
    }
}
#endif
