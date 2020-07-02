#include "GamePause.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

namespace abyss::Event
{
    GamePause::GamePause()
    {}
    void GamePause::onStart()
    {
        m_pManager->getModule<GlobalTime>()->pause();
    }
    bool GamePause::update([[maybe_unused]]double dt)
    {
        return true;
    }
    void GamePause::onEnd()
    {
        m_pManager->getModule<GlobalTime>()->resume();
    }
}
