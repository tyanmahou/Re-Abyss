#include "StateChecker.hpp"

namespace abyss::Actor::Player
{
    StateChecker::StateChecker(IActor* pActor):
        m_pActor(pActor)
    {}

    void StateChecker::onStateStart()
    {
        m_canDoorState = false;
    }
}
