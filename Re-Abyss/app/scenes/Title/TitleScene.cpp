#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/modules/Cycle/Title/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Cycle/Common/Loading.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss
{
    class TitleScene::Impl :
        public Cycle::Title::IMainObserver
    {
        std::unique_ptr<Cycle::Title::Main> m_main;

        std::function<void()> m_onGameStartFunc;

        Cycle::Loading m_loading;
    public:
        Impl([[maybe_unused]]const InitData& init)
        {
            //m_loading.start([this]() {
            //    this->reload();
            //    auto wait = [&]()->Coro::Task<void> {
            //        [[maybe_unused]]s3d::Array<int8> dummy;
            //        while(true) {
            //            co_yield Coro::WaitForSeconds(1s);
            //        }
            //        co_return;
            //    }();
            //    while (wait.moveNext()) {
            //        //Debug::Log::PrintCache << *progress;
            //    }
            //});

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
            if (!m_loading.isDone()) {
                return;
            }
            m_main->update();
        }

        void draw() const
        {
            if (!m_loading.isDone()) {
                m_loading.draw();
                return;
            }
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
