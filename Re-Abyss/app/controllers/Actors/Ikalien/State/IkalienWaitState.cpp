#include "IkalienWaitState.hpp"
#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
namespace abyss
{
    void IkalienWaitState::update([[maybe_unused]]double dt)
    {
        if (m_actor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(IkalienActor::State::Pursuit);
        }
    }

    void IkalienWaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }

}
