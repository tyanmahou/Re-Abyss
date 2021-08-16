#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

#include <abyss/system/System.hpp>
#include <abyss/system/Title/Booter.hpp>

namespace abyss
{
    class TitleScene::Impl :
        public Cycle::Title::IMasterObserver
    {
        using System = Sys::System<Sys::Config::Title()>;
        std::unique_ptr<System> m_system;

        std::function<void()> m_onGameStartFunc;
    public:
        Impl([[maybe_unused]]const InitData& init)
        {
        }

        void loading()
        {
            Resource::Assets::Main()->release();
            Resource::Preload::Preloader preloader(U"@Cycle/Title");
            preloader.preload();

            this->init();
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
            m_system = std::make_unique<System>();
            auto booter = std::make_unique<Sys::Title::Booter>(this);
            m_system->boot(booter.get());
        }
        void update()
        {
            m_system->update();
        }

        void draw() const
        {
            m_system->draw();
        }

        bool onGameStart() final
        {
            m_onGameStartFunc();
            return true;
        }
        bool onExit() final
        {
            // 閉じる
            s3d::System::Exit();
            return true;
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

        // ローディング
        m_pImpl->loading();

#if ABYSS_NO_BUILD_RESOURCE
        m_reloader
            .setMessage(U"Title")
            .setCallback([this]() {
            this->m_pImpl->reload();
        }).setSuperCallback([this] {
            this->m_pImpl->reload();
        });
#endif
    }

    void TitleScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void TitleScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
