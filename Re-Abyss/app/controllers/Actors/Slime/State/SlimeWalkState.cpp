#include "SlimeWalkState.hpp"
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>

namespace abyss
{
    void SlimeWalkState::onColisionMapUp()
    {
        m_onCollision = true;
    }
    void SlimeWalkState::start()
    {
        m_body->setSize({ 35, 25 }).setPivot({ 0, 7.5 });
    }
    void SlimeWalkState::update(double dt)
    {
        SlimeBaseState::update(dt);

        s3d::Vec2 d = m_actor->getWorld()->getPlayerPos() - m_body->getPos();
        if (m_onCollision && m_body->getVelocity().x * d.x > 0 && d.length() <= 200) {
            this->changeState(SlimeActor::Jump);
        }
        m_onCollision = false;
    }
    void SlimeWalkState::draw() const
    {
        m_actor->getBindedView()->drawWalk();
    }
}
