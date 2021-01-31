#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/modules/Cycle/Title/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

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
        }

        Coro::Generator<double> loading()
        {
            Resource::Assets::Main()->release();
            Resource::Preload::Preloader preloader(U"Cycle/title.json");
            for (auto p : preloader.preloadProgress()) {
                co_yield p;
            }

            this->init();
            co_yield 1.0;
        }

#if ABYSS_NO_BUILD_RESOURCE
        void reload()
        {
            Resource::Assets::Main()->release();

            Resource::Preload::LoadCycleCommon();
            Resource::Preload::LoadTitleToml();

            this->init();
        }
#endif
        void init()
        {
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
#if ABYSS_NO_BUILD_RESOURCE
        m_reloader
            .setMessage(U"Title")
            .setCallback([this]() {
            this->m_pImpl->reload();
        }).setSuperCallback([this] {
            this->m_pImpl->reload();
        });
#endif

        m_loading.start(m_pImpl->loading());
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
