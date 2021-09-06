#include "JumpState.hpp"
#include "WalkState.hpp"

#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void JumpState::start()
    {
        m_audio->play(U"Jump");
        m_body->setSize(Param::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(Param::Jump::JumpHeight);
        m_motion->set(Motion::Jump);
    }
    void JumpState::update()
    {
        this->updateMove();
    }
    void JumpState::lastUpdate()
    {
        if (m_mapCol->isHitGround()) {
            this->changeState<WalkState>();
        }
        this->checkWallHit();
    }
}
