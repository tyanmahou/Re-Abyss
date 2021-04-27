#include "WalkState.hpp"
#include "JumpState.hpp"
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    Task<> WalkState::start()
    {
        m_body->setSize(Param::Walk::Size).setPivot(Param::Walk::Pivot);
        co_return;
    }
    void WalkState::update()
    {
        BaseState::update();

        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        if (m_mapCol->isHitGround() && m_body->getVelocity().x * d.x > 0 && d.length() <= Param::Walk::SearchRange) {
            this->changeState<JumpState>();
        }
    }
    void WalkState::draw()const
    {
        (*m_view)->drawWalk();
    }
}
