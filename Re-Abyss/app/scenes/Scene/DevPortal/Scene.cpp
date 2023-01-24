#include <abyss/scenes/Scene/DevPortal/Scene.hpp>
#include <abyss/debugs/Debug.hpp>
#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#include <abyss/modules/Devs/GitHub/TaskBoard.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Layout/Window/Window.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Constants.hpp>
#if ABYSS_DEVELOP

namespace abyss::Scene::DevPortal
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s),
            m_gitHub(),
            m_task(&m_gitHub)
        {
        }

        void update()
        {
            if (KeyEnter.down()) {
                m_data->isRequestedSceneEnd = true;
                m_data->result = SceneResult{
                    .command = SceneResult::GameStart
                };
            } else if (KeyE.down()) {
                m_data->isRequestedSceneEnd = true;
                m_data->result = SceneResult{
                    .command = SceneResult::Experience
                };
            }
        }
        void draw()
        {
            s3d::Scene::Rect().draw(ColorDef::DefaultFadeColor);
            m_font(U"[DevPortal] Push Enter Start").draw();
            m_task.draw();
        }
    private:
        std::shared_ptr<Data_t> m_data;
        Font m_font{ 20 };

        GitHub m_gitHub;
        Devs::GitHub::TaskBoard m_task;
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
