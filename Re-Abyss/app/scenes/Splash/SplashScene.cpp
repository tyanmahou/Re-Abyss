#include "SplashScene.hpp"
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/modules/Cycle/Splash/Main.hpp>
#include <abyss/debugs/Log/Log.hpp>

#include <abyss/system/System.hpp>
#include <abyss/system/Splash/Booter.hpp>

namespace abyss
{
    class SplashScene::Impl : 
        public Cycle::Splash::IMainObserver
    {
        using System = Sys::System<Sys::Config::Splash()>;
        std::unique_ptr<System> m_system;

        std::unique_ptr<Cycle::Splash::Main> m_main;

        std::function<void()> m_changeOpDemoSceneFunc;

        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]]const InitData& init):
            m_data(init._s)
        {
        }

        void initSystem()
        {
            m_system = std::make_unique<System>();
            auto booter = std::make_unique<Sys::Splash::Booter>();
            m_system->boot(booter.get());

            m_main = std::make_unique<Cycle::Splash::Main>(this);
        }
        void loading()
        {
            // 最初にToml全部ロード
            Resource::Preload::LoadTomlAll();
            Resource::Assets::Main()->release();

            Resource::Preload::Preloader preloader(U"@Cycle/Splash");
            preloader.preload();

            this->initSystem();
        }
        void update()
        {
            m_system->update();
            m_main->update();
        }

        void draw() const
        {
            m_system->draw();
            m_main->draw();
        }

       void chageOpDemoScene() final
       {
           m_changeOpDemoSceneFunc();
       }

       void bindChangeOpDemoScene(const std::function<void()>& callback)
       {
           m_changeOpDemoSceneFunc = callback;
       }
    };
    SplashScene::SplashScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindChangeOpDemoScene([this] {
            // TODO OpDemoに変更
            this->changeScene(SceneName::Title, 0);
        });

        // ローディング
        m_pImpl->loading();
    }

    void SplashScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void SplashScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
