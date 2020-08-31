#include "TitleScene.hpp"
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/controllers/Cycle/Title/Main.hpp>

namespace abyss
{
    class TitleScene::Impl :
        public Cycle::Title::IMainObserver
    {
        std::unique_ptr<Cycle::Title::Main> m_main;
    public:
        Impl([[maybe_unused]]const InitData& init)
        {
            Resource::Prelaod::LoadTitleToml(init._s->m_resource);

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
    };
    TitleScene::TitleScene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}

    void TitleScene::update()
    {
        m_pImpl->update();
    }

    void TitleScene::draw() const
    {
        m_pImpl->draw();
    }
}
