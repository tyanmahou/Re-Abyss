#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/Cycle/Title/Logo/Logo.hpp>

namespace abyss::Cycle::Title
{
    Main::Main(IMainObserver* observer) :
        m_observer(observer),
        m_logo(std::make_unique<Logo::Logo>()),
        m_bgm(ResourceManager::Main()->loadAudio(U"bgm/cycle/title/title.aas"))
    {
        m_bgm.play();
    }

    Main::~Main()
    {}

    void Main::update()
    {
        m_logo->update();
    }

    void Main::draw() const
    {
        m_logo->draw();
    }
}
