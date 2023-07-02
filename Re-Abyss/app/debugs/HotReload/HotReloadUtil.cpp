#include <abyss/debugs/HotReload/HotReloadUtil.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

namespace abyss::Debug
{
    using namespace abyss::Resource;

    void HotReloadUtil::ReloadAssetCommon()
    {
        // Temporray
        {
            auto* pAssets = Assets::Temporray();
            // 最初にParam全部ロード
            {
                auto preloader = Preload::ParamAll();
                preloader.append(U"Common/Message"); // Message
                preloader.preload(pAssets);
            }
            // Message
            {
                Msg::Manager::Load(Msg::Language::Ja(), pAssets);
            }
            // キャッシュ削除
            pAssets->release();
        }

        // Norelease
        {
            auto* pAssets = Assets::Norelease();
            pAssets->release();
            Resource::Preload::Preloader norelease(U"Norelease");
            norelease.preload(pAssets);
        }

        Assets::Main()->release();
    }
}
#endif
