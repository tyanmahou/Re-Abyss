#include <abyss/scenes/Scene/Splash/Scene.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>

#include <abyss/scenes/System/System.hpp>
#include <abyss/scenes/Scene/Splash/Booter.hpp>

namespace abyss::Scene::Splash
{
    class Scene::Impl :
        public Cycle::Splash::IMasterObserver
    {
        using System = Sys::System<Sys::Config::Splash()>;
        std::unique_ptr<System> m_system;

        std::function<void()> m_changeOpDemoSceneFunc;

        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]] const InitData& init) :
            m_data(init._s)
        {}

        void initSystem()
        {
            m_system = std::make_unique<System>();
            auto booter = std::make_unique<Booter>(this);
            m_system->boot(booter.get());
        }
        void loading()
        {
            {
                Resource::Preload::Preloader preloader(U"Scene/Splash");
                preloader.preload();
            }
            this->initSystem();
        }
        void update()
        {
            m_system->update();
        }

        void draw() const
        {
            m_system->draw();
        }

        bool chageOpDemoScene() final
        {
            m_data->isRequestedSceneEnd = true;

            return true;
        }
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        // ローディング
        m_pImpl->loading();
    }
    Scene::~Scene()
    {}
    void Scene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void Scene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
