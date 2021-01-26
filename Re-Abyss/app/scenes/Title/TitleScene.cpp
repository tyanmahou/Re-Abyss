#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/modules/Cycle/Title/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Cycle/Common/Loading/LoadingView.hpp>

namespace abyss
{
    class TitleScene::Impl :
        public Cycle::Title::IMainObserver
    {
        std::unique_ptr<Cycle::Title::Main> m_main;

        std::function<void()> m_onGameStartFunc;

        Cycle::LoadingView m_loading;
    public:
        Impl([[maybe_unused]]const InitData& init)
        {
            this->reload();

            m_main = std::make_unique<Cycle::Title::Main>(this);
        }

        void reload()
        {
            Resource::Assets::Main()->release();

            Resource::Prelaod::LoadTitleToml();
            Resource::Prelaod::LoadCycleCommon();
        }
        void update()
        {
            m_main->update();
        }

        void draw() const
        {
            m_main->draw();
            m_loading.draw();
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

        m_reloader
            .setMessage(U"Title")
            .setCallback([this]() {
            this->m_pImpl->reload();
        }).setSuperCallback([this] {
            this->m_pImpl->reload();
        });
    }

    void TitleScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void TitleScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
    void TitleScene::finally()
    {
        m_pImpl->finally();
    }
}
