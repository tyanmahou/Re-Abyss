#include "WaitState.hpp"
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/System/System.hpp>
namespace abyss::Ikalien
{
    void WaitState::update([[maybe_unused]]double dt)
    {
        if (m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(State::Pursuit);
        }
    }

    void WaitState::draw() const
    {
        m_pActor->getBindedView()->drawWait();
    }

}
