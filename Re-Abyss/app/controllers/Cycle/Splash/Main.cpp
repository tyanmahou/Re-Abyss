#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/controllers/Cycle/Splash/Logo/Logo.hpp>

namespace abyss::Cycle::Splash
{
    Main::Main(IMainObserver* observer):
        m_observer(observer),
        m_logo(std::make_unique<Logo::Logo>())
    {}

    void Main::update()
    {
        if (InputManager::Start.down() || m_logo->isEnd()) {
            m_observer->chageTitleScene();
        }
    }

    void Main::draw() const
    {
        m_logo->draw();
    }
}
