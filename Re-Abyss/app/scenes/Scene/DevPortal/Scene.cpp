#include <abyss/scenes/Scene/DevPortal/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/scenes/Scene/DevPortal/Booter.hpp>
#include <abyss/scenes/Sys/System.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <Siv3D.hpp>

namespace abyss::Scene::DevPortal
{
    class Scene::Impl final:
        public Cycle::DevPortal::IMasterObserver
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
            this->init();
        }

        void init()
        {
            m_system = Factory::System::DevPortal(m_data.get())
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
    public:
        bool onGameStart() override
        {
            return this->onSceneEnd({
                .command = SceneResult::GameStart
            });
        }
        bool onExperiment() override
        {
            return this->onSceneEnd({
                .command = SceneResult::Experience
            });
        }
        bool onSceneEnd(const SceneResult& result)
        {
            m_data->isRequestedSceneEnd = true;
            m_data->result = result;
            return true;
        }
    private:
        std::shared_ptr<Sys::System> m_system;
        std::shared_ptr<Data_t> m_data;
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
