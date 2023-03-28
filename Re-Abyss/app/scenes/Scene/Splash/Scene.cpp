#include <abyss/scenes/Scene/Splash/Scene.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/Sys/System.hpp>
#include <abyss/scenes/Scene/Splash/Booter.hpp>

namespace abyss::Scene::Splash
{
    class Scene::Impl :
        public Cycle::Splash::IMasterObserver
    {
    public:
        Impl([[maybe_unused]] const InitData& init) :
            m_data(init._s)
        {}

        void initSystem()
        {
            m_system = Factory::System::DevPortal(m_data.get())
                .instantiate<Sys2::System>();
            m_system->boot<Booter>(this);
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
    private:
        std::unique_ptr<Sys2::System> m_system;
        std::shared_ptr<Data_t> m_data;
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
