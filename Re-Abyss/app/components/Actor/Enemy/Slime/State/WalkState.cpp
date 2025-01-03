﻿#include <abyss/components/Actor/Enemy/Slime/State/WalkState.hpp>
#include <abyss/components/Actor/Enemy/Slime/State/JumpState.hpp>

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void WalkState::start()
    {
        m_body->setSize(Param::Walk::Size).setOffset(Vec2::Zero());
        m_motion->set(Motion::Walk);
    }
    void WalkState::update()
    {
        this->updateMove();

        s3d::Vec2 d = ActorUtils::ToPlayer(*m_pActor, *m_body);
        if (m_mapCol->isHitGround() && m_body->getVelocity().x * d.x > 0 && d.length() <= Param::Walk::SearchRange) {
            this->changeState<JumpState>();
            return;
        }
    }
    void WalkState::lastUpdate()
    {
        this->checkWallHit();
    }
}
