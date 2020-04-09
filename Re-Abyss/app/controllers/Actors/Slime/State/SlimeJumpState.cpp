#include "SlimeJumpState.hpp"

#include <abyss/views/Actors/Slime/SlimeVM.hpp>
#include <abyss/params/Actors/Slime/SlimeParam.hpp>
namespace abyss
{
    void SlimeJumpState::onColisionMapUp()
    {
        this->changeState(SlimeActor::Walk);
    }
    void SlimeJumpState::start()
    {
        m_body->setSize(SlimeParam::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(SlimeParam::Jump::JumpHeight);
    }
    void SlimeJumpState::draw() const
    {
        m_actor->getBindedView()->drawJump();
    }
}
