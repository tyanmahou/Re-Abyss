#include "SplashScene.hpp"
#include <abyss/controllers/Cycle/Splash/Main.hpp>

namespace abyss
{
    class SplashScene::Impl : 
        public Cycle::Splash::IMainObserver
    {
        std::unique_ptr<Cycle::Splash::Main> m_main;

        std::function<void()> m_changeTitleSceneFunc;
    public:
        Impl([[maybe_unused]]const InitData& init):
            m_main(std::make_unique<Cycle::Splash::Main>(this))
        {}

        void update()
        {
            m_main->update();
        }

        void draw() const
        {
            m_main->draw();
        }

       void chageTitleScene() final
       {
           m_changeTitleSceneFunc();
       }

       void bindChangeTitleScene(const std::function<void()>& callback)
       {
           m_changeTitleSceneFunc = callback;
       }
    };
    SplashScene::SplashScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindChangeTitleScene([this] {
            // TODO Titleに変更
            this->changeScene(SceneName::Main);
        });
    }

    void SplashScene::update()
    {
        m_pImpl->update();
    }

    void SplashScene::draw() const
    {
        m_pImpl->draw();
    }
}
