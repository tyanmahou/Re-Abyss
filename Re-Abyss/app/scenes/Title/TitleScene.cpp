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

        std::function<void()> m_onGameStartFunc;
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

        void onGameStart() final
        {
            m_onGameStartFunc();
        }
        void onExit() final
        {
            // 閉じる
            s3d::System::Exit();
        }

        void bindGameStartFunc(const std::function<void()>& callback)
        {
            m_onGameStartFunc = callback;
        }
    };
    TitleScene::TitleScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindGameStartFunc([this] {
            this->changeScene(SceneName::SaveSelect);
        });
    }

    void TitleScene::update()
    {
        m_pImpl->update();
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
