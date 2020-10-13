#include "SaveSelectScene.hpp"

namespace abyss
{
    class SaveSelectScene::Impl
    {
    public:
        Impl([[maybe_unused]] const InitData& init)
        {
        }

        void update()
        {
        }

        void draw() const
        {
        }

        void finally()
        {
        }
    };
    SaveSelectScene::SaveSelectScene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
    }

    void SaveSelectScene::update()
    {
        m_pImpl->update();
    }

    void SaveSelectScene::draw() const
    {
        m_pImpl->draw();
    }
    void SaveSelectScene::finally()
    {
        m_pImpl->finally();
    }
}
