#include "SplashScene.hpp"
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/modules/Cycle/Splash/Main.hpp>
#include <abyss/debugs/Log/Log.hpp>
namespace abyss
{
    class SplashScene::Impl : 
        public Cycle::Splash::IMainObserver
    {
        std::unique_ptr<Cycle::Splash::Main> m_main;

        std::function<void()> m_changeOpDemoSceneFunc;

        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]]const InitData& init):
            m_data(init._s)
        {
        }

        Coro::Generator<double> loading()
        {
            // 最初にToml全部ロード
            Resource::Preload::LoadTomlAll();
            Resource::Assets::Main()->release();

            Resource::Preload::Preloader preloader(U"@Cycle/splash");
            for (auto p : preloader.preloadProgress()) {
                co_yield p;
            }

            m_main = std::make_unique<Cycle::Splash::Main>(this);
            co_yield 1.0;
        }
        void update()
        {
            m_main->update();
        }

        void draw() const
        {
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

        m_loading.start(m_pImpl->loading());
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
