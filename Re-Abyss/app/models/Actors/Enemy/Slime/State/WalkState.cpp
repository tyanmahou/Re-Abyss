#include "WalkState.hpp"
#include "JumpState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

namespace abyss::Slime
{
    void WalkState::start()
    {
        m_body->setSize(Param::Walk::Size).setPivot(Param::Walk::Pivot);
        m_draw->request(DrawModel::Kind::Walk);
    }
    void WalkState::update(double dt)
    {
        BaseState::update(dt);

        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        if (m_mapCol->isHitGround() && m_body->getVelocity().x * d.x > 0 && d.length() <= Param::Walk::SearchRange) {
            this->changeState<JumpState>();
        }
    }
}
