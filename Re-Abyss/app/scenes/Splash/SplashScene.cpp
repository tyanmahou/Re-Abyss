#include "SplashScene.hpp"

namespace abyss
{
    class SplashScene::Impl
    {
    public:
        Impl([[maybe_unused]]const InitData& init)
        {}

        void update()
        {
        }

        void draw() const
        {

        }
    };
    SplashScene::SplashScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}

    void SplashScene::update()
    {
        m_pImpl->update();
        if (KeyEnter.down()) {
            this->changeScene(SceneName::Main);
        }
    }

    void SplashScene::draw() const
    {
        m_pImpl->draw();
    }
}
