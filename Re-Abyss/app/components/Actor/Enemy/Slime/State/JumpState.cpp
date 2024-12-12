#include <abyss/components/Actor/Enemy/Slime/State/JumpState.hpp>
#include <abyss/components/Actor/Enemy/Slime/State/WalkState.hpp>
#include <abyss/components/Actor/Enemy/Slime/SeDef.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void JumpState::start()
    {
        m_audio->play(SeDef::Jump);
        m_body->setSize(Param::Jump::Size).setOffset(Param::Jump::Offset);

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
