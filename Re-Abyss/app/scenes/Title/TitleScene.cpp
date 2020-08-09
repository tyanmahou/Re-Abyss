#include "TitleScene.hpp"

namespace abyss
{
    class TitleScene::Impl
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
    TitleScene::TitleScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}

    void TitleScene::update()
    {
        m_pImpl->update();
        if (KeyEnter.down()) {
            this->changeScene(SceneName::Main);
        }
    }

    void TitleScene::draw() const
    {
        m_pImpl->draw();
    }
}
