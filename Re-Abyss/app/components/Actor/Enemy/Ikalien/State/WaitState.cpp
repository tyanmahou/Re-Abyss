#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    Task<> WaitState::start()
    {
        co_return;
    }
    void WaitState::update()
    {
        if (m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<PursuitState>();
        }
    }

    void WaitState::draw() const
    {
        (*m_view)->drawWait();
    }
}
