#include "OpDemoScene.hpp"

namespace abyss
{
    class OpDemoScene::Impl
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
    OpDemoScene::OpDemoScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}

    void OpDemoScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void OpDemoScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
