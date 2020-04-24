#include "WaitState.hpp"
#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
namespace abyss::Ikalien
{
    void WaitState::update([[maybe_unused]]double dt)
    {
        if (m_actor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(State::Pursuit);
        }
    }

    void WaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }

}
