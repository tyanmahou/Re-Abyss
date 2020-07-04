#include "GamePause.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>

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
        if (m_waitFlag) {
            m_waitFlag = false;
            return true;
        }
        if (InputManager::Start.down()) {
            return false;
        }
        return true;
    }
    void GamePause::onEnd()
    {
        m_pManager->getModule<GlobalTime>()->resume();
    }
}
