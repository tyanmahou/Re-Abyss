#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    void WaitState::start()
    {
        m_motion->set(Motion::Wait);
    }
    void WaitState::update()
    {
        if (m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<PursuitState>();
        }
    }
}
