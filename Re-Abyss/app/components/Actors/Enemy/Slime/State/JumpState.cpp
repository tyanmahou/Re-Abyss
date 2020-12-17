#include "JumpState.hpp"
#include "WalkState.hpp"

#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void JumpState::start()
    {
        Debug::Log::PrintCache << U"jump";
        m_pActor->find<AudioSource>()->play(U"Jump");
        m_body->setSize(Param::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(Param::Jump::JumpHeight);
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
