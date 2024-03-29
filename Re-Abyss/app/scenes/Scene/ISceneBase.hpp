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

        template<class Self>
        decltype(auto) fader(this Self&& self)
        {
            return std::forward_like<Self>(self.getData().fader);
        }
        template<class Self>
        decltype(auto) loader(this Self&& self)
        {
            return std::forward_like<Self>(self.getData().loader);
        }
    public:
        using SceneManager::Scene::Scene;

        void update() final;
        void draw() const final;
    protected:
#if ABYSS_DEBUG
        Debug::HotReload m_reloader;
#endif
    };
}
