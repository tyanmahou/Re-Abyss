#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/controllers/Cycle/Title/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss
{
    class TitleScene::Impl :
        public Cycle::Title::IMainObserver
    {
        std::unique_ptr<Cycle::Title::Main> m_main;
    public:
        Impl([[maybe_unused]]const InitData& init)
        {
            Resource::Prelaod::LoadTitleToml(init._s->m_resource);

            m_main = std::make_unique<Cycle::Title::Main>(this);
        }

        void update()
        {
            m_main->update();
        }

        void draw() const
        {
            m_main->draw();
        }

        void finally()
        {
            m_main->finally();
        }
    };
    TitleScene::TitleScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}

    void TitleScene::update()
    {
        m_pImpl->update();
        if (InputManager::Start.down()) {
            changeScene(SceneName::Main);
        }
        if (KeyBackspace.down()) {
            changeScene(SceneName::Splash);
        }
    }

    void TitleScene::draw() const
    {
        m_pImpl->draw();
    }
    void TitleScene::finally()
    {
        m_pImpl->finally();
    }
}
