# pragma once
#include <Siv3D.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>
#include <abyss/commons/Loading/Loading.hpp>
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

        void changeScene(const SceneKind& state, int transitionTimeMillisec = 1000, const CrossFade crossFade = CrossFade::No)
        {
            this->getData().fromScene = this->getState();
            this->getData().toScene = state;
            this->AppScene::Scene::changeScene(state, transitionTimeMillisec, crossFade);
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
