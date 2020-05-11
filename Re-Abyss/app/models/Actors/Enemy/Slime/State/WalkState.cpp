#include "WalkState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

namespace abyss::Slime
{
    void WalkState::onColisionMapUp()
    {
        m_onCollision = true;
    }
    void WalkState::start()
    {
        m_body->setSize(Param::Walk::Size).setPivot(Param::Walk::Pivot);
    }
    void WalkState::update(double dt)
    {
        BaseState::update(dt);

        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        if (m_onCollision && m_body->getVelocity().x * d.x > 0 && d.length() <= Param::Walk::SearchRange) {
            this->changeState(State::Jump);
        }
    }
    void WalkState::onReflesh()
    {
        m_onCollision = false;
    }
    void WalkState::draw() const
    {
        m_pActor->getBindedView()->drawWalk();
    }
}
