#include <abyss/scenes/Scene/Boot/Initializer.hpp>
#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

namespace abyss::Scene::Boot
{
    using namespace abyss::Resource;

    void Initializer::LoadAsset()
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

        // NoRelease
        {
            auto* pAssets = Assets::NoRelease();
            Resource::Preload::Preloader preloader(U"NoRelease");
            preloader.preload(pAssets);
        }
    }
    void Initializer::ReloadParamAll()
    {
        auto* pAssets = Assets::Temporray();
        auto preloader = Preload::ParamAll();
        preloader.preload(pAssets);
        pAssets->release();
    }
    void Initializer::ReloadMsg()
    {
        auto* pAssets = Assets::Temporray();
        Preload::Preloader preloader{U"Common/Message"};
        preloader.preload(pAssets);
        Msg::Manager::Load(Msg::Language::Ja(), pAssets);
        pAssets->release();
    }
    void Initializer::ReloadNoRelease()
    {
        auto* pAssets = Assets::NoRelease();
        Resource::Preload::Preloader preloader(U"NoRelease");
        preloader.preload(pAssets);
    }
}
