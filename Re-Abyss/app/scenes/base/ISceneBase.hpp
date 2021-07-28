# pragma once
#include <Siv3D.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>
#include <abyss/commons/Loading/Loading.hpp>

namespace abyss
{
    /// <summary>
    /// game shared data
    /// </summary>
    struct GameData
    {
        String m_fromScene;
        String m_toScene;
    };

    using AppScene = SceneManager<String, GameData>;

    class ISceneBase : public AppScene::Scene
    {
    protected:
        virtual void onSceneUpdate() = 0;
        virtual void onSceneDraw()const = 0;

        virtual void finally() {}

        void changeScene(const String& state, int transitionTimeMillisec = 1000, bool crossFade = false)
        {
            this->getData().m_fromScene = std::move(this->getData().m_toScene);
            this->getData().m_toScene = state;
            this->finally();
            this->AppScene::Scene::changeScene(state, transitionTimeMillisec, crossFade);
        }
    public:
        using AppScene::Scene::Scene;

        void update() final;
        void draw() const final;
    protected:
        Loading m_loading;
#if ABYSS_NO_BUILD_RESOURCE
        Debug::HotReload m_reloader;
#endif
    };

    namespace SceneName
    {
#define ABYSS_SCENE_NAME(name) inline constexpr auto name = U#name

        ABYSS_SCENE_NAME(Splash);
        ABYSS_SCENE_NAME(OpDemo);
        ABYSS_SCENE_NAME(Title);
        ABYSS_SCENE_NAME(SaveSelect);
        ABYSS_SCENE_NAME(Main);

#undef ABYSS_SCENE_NAME
    }
}