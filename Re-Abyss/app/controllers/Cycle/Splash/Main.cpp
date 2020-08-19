#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Cycle::Splash
{
    Main::Main(IMainObserver* observer):
        m_observer(observer)
    {}

    void Main::update()
    {
        if (InputManager::Start.down()) {
            m_observer->chageTitleScene();
        }
    }

    void Main::draw() const
    {}
}
