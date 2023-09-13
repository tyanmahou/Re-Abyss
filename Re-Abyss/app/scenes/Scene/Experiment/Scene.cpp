#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/scenes/Scene/Experiment/Booter.hpp>
#include <abyss/scenes/Sys/System.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace abyss::Scene::Experiment
{
    class Scene::Impl final :
        public Cycle::Experiment::IMasterObserver
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
        }

        void init()
        {
            m_system = Factory::System::Experiment(m_data.get())
                .instantiate<Sys::System>();
            m_system->boot<Booter>(this);
        }
        void update()
        {
            m_system->update();
        }
        void draw()
        {
            m_system->draw();
        }
        bool onExit() override
        {
            m_data->isRequestedSceneEnd = true;
            return true;
        }
    private:
        std::shared_ptr<Sys::System> m_system;
        std::shared_ptr<Data_t> m_data;
        Font m_font{ 20 };
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
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
#endif
