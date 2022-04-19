# pragma once
#include <Siv3D.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>
#include <abyss/commons/Loading/Loading.hpp>
#include <abyss/scenes/base/GameData.hpp>

namespace abyss
{
    using AppScene = SceneManager<String, GameData>;

    class ISceneBase : public AppScene::Scene
    {
    protected:
        virtual void onSceneUpdate() = 0;
        virtual void onSceneDraw()const = 0;

        void changeScene(const String& state, int transitionTimeMillisec = 1000, const CrossFade crossFade = CrossFade::No)
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

    namespace SceneName
    {
#define ABYSS_SCENE_NAME(name) inline constexpr auto name = U#name

        ABYSS_SCENE_NAME(Root);
        ABYSS_SCENE_NAME(Splash);
        ABYSS_SCENE_NAME(OpDemo);
        ABYSS_SCENE_NAME(Title);
        ABYSS_SCENE_NAME(SaveSelect);
        ABYSS_SCENE_NAME(Main);

#undef ABYSS_SCENE_NAME
    }
}