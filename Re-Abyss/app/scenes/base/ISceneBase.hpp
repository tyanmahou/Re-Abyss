# pragma once
#include <Siv3D.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>
#include <abyss/scenes/Loading/Loading.hpp>
#include <abyss/scenes/base/GameData.hpp>
#include <abyss/scenes/SceneKind.hpp>

namespace abyss
{
    using AppScene = SceneManager<SceneKind, GameData>;

    class ISceneBase : public AppScene::Scene
    {
    protected:
        virtual void onSceneUpdate() = 0;
        virtual void onSceneDraw()const = 0;

        void requestSceneEnd()
        {
            this->getData().isRequestedSceneEnd = true;
        }
    public:
        using AppScene::Scene::Scene;

        void update() final;
        void draw() const final;
    protected:
        Loading m_loading;
#if ABYSS_NO_BUILD_RESOURCE && ABYSS_DEBUG
        Debug::HotReload m_reloader;
#endif
    };
}
