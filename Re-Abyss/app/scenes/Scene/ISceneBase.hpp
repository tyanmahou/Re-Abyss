# pragma once
#include <abyss/scenes/Scene/SceneManager.hpp>
#include <abyss/debugs/HotReload/HotReload.hpp>
#include <abyss/scenes/Loading/Loading.hpp>

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
    public:
        using SceneManager::Scene::Scene;

        void update() final;
        void draw() const final;
    protected:
        Loading m_loading;
#if ABYSS_NO_BUILD_RESOURCE && ABYSS_DEBUG
        Debug::HotReload m_reloader;
#endif
    };
}
