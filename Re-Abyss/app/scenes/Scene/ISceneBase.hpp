# pragma once
#include <abyss/scenes/Scene/SceneManager.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>

namespace abyss
{
    class ISceneBase : public SceneManager::Scene
    {
    protected:
        virtual void onSceneUpdate() = 0;
        virtual void onSceneDraw()const = 0;

        void requestSceneEnd()
        {
            this->getData().isRequestedSceneEnd = true;
        }

        Fade::SceneFader& fader()
        {
            return this->getData().fader;
        }
        const Fade::SceneFader& fader() const
        {
            return this->getData().fader;
        }
        Loading::Loader& loader()
        {
            return this->getData().loader;
        }
        const Loading::Loader& loader() const
        {
            return this->getData().loader;
        }
    public:
        using SceneManager::Scene::Scene;

        void update() final;
        void draw() const final;
    protected:
#if ABYSS_NO_BUILD_RESOURCE && ABYSS_DEBUG
        Debug::HotReload m_reloader;
#endif
    };
}
