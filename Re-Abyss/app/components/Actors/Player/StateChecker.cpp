#include "StateChecker.hpp"

namespace abyss::Actor::Player
{
    StateChecker::StateChecker(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void StateChecker::onStateStart()
    {
        m_canDoorState = false;
    }
}
