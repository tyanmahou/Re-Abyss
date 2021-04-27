#include "JumpState.hpp"
#include "WalkState.hpp"

#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    Task<> JumpState::start()
    {
        m_pActor->find<AudioSource>()->play(U"Jump");
        m_body->setSize(Param::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(Param::Jump::JumpHeight);
        co_return;
    }
    void JumpState::lastUpdate()
    {
        if (m_mapCol->isHitGround()) {
            this->changeState<WalkState>();
        }
        BaseState::lastUpdate();
    }

    void JumpState::draw()const
    {
        (*m_view)->drawJump();
    }
}
