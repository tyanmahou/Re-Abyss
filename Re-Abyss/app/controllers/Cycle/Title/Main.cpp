#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/Cycle/Title/Logo/Logo.hpp>
#include <abyss/controllers/Cycle/Title/BackGround/BackGround.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title
{
    Main::Main(IMainObserver* observer) :
        m_observer(observer),
        m_logo(std::make_unique<Logo::Logo>()),
        m_bg(std::make_unique<BackGround::BackGround>()),
        m_bgm(ResourceManager::Main()->loadAudio(U"bgm/cycle/title/title.aas"))
    {
        m_bgm.play();
    }

    Main::~Main()
    {}

    void Main::update()
    {
        m_logo->update();
        if (!m_logo->isEnd()) {
            return;
        }
        m_bg->update();
    }

    void Main::draw() const
    {
        if (m_logo->isEnd()) {
            m_bg->draw();
        }
        m_logo->draw();

    }
}
