#include <abyss/debugs/HotReload/HotReloadUtil.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/scenes/Scene/Boot/Initializer.hpp>

namespace
{
    using namespace abyss;

    bool IsShaderAsset(const s3d::FileChange& c)
    {
        return c.path.includes(Path::ShaderPath);
    }
    bool IsParamAsset(const s3d::FileChange& c)
    {
        return c.path.includes(Path::ParamPath);
    }
    bool IsMsgAsset(const s3d::FileChange& c)
    {
        return c.path.includes(Path::MsgPath);
    }
}
namespace abyss::Debug
{
    using namespace abyss::Resource;

    void HotReloadUtil::ReloadAssetCommon(const Debug::FileChanges& changes)
    {
        if (changes.empty()) {
            return;
        }
        // changesに合わせて必要なものだけリロード
        Assets::Main()->release();
        if (changes.any(::IsShaderAsset)) {
            Assets::Norelease()->release();
            Scene::Boot::Initializer::ReloadNoRelease();
        }
        Assets::Temporray()->release();
        if (changes.any(::IsParamAsset)) {
            Scene::Boot::Initializer::ReloadParamAll();
        }
        if (changes.any(::IsMsgAsset)) {
            Scene::Boot::Initializer::ReloadMsg();
        }
    }
}
#endif
