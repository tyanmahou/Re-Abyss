#include "SlimeWalkState.hpp"
#include <abyss/controllers/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>
#include <abyss/params/Actors/Slime/SlimeParam.hpp>

namespace abyss
{
    void SlimeWalkState::onColisionMapUp()
    {
        m_onCollision = true;
    }
    void SlimeWalkState::start()
    {
        m_body->setSize(SlimeParam::Walk::Size).setPivot(SlimeParam::Walk::Pivot);
    }
    void SlimeWalkState::update(double dt)
    {
        SlimeBaseState::update(dt);

        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
        if (m_onCollision && m_body->getVelocity().x * d.x > 0 && d.length() <= SlimeParam::Walk::SearchRange) {
            this->changeState(SlimeActor::Jump);
        }
        m_onCollision = false;
    }
    void SlimeWalkState::draw() const
    {
        m_actor->getBindedView()->drawWalk();
    }
}
