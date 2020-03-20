#include "SlimeJumpState.hpp"

#include <abyss/views/Actors/Slime/SlimeVM.hpp>

namespace abyss
{
    void SlimeJumpState::onColisionMapUp()
    {
        this->changeState(SlimeActor::Walk);
    }
    void SlimeJumpState::start()
    {
        m_body->setSize({ 32, 32 }).setPivot({ 0, 0 });

        m_body->jumpToHeight(80);
    }
    void SlimeJumpState::draw() const
    {
        m_actor->getBindedView()->drawJump();
    }
}
