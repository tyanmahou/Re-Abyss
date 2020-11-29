#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/controllers/System/System.hpp>
namespace abyss::Actor::Enemy::Ikalien
{
    void WaitState::start()
    {
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
