#include <abyss/scenes/Scene/DevPortal/Scene.hpp>
#include <abyss/debugs/Debug.hpp>
#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#include <Siv3D.hpp>

#if ABYSS_DEVELOP
namespace abyss::Scene::DevPortal
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
            Debug::Log::Info(U"Todo");
            for (auto&& issue : m_gitHub.getIssues(U"Todo")) {
                Debug::Log::Info(issue.title);
            }
            Debug::Log::Info(U"In Progress");
            for (auto&& issue : m_gitHub.getIssues(U"In Progress")) {
                Debug::Log::Info(issue.title);
            }
        }

        void update()
        {
            if (KeyEnter.down()) {
                m_data->isRequestedSceneEnd = true;
            }
        }
        void draw()
        {
            m_font(U"[DevPortal] Push Enter Start").draw();
        }
    private:
        std::shared_ptr<Data_t> m_data;
        Devs::GitHub::GitHub m_gitHub;
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
