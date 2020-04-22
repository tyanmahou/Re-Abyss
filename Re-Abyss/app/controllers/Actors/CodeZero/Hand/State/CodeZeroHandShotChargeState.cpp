#include "CodeZeroHandShotChargeState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    CodeZeroHandShotChargeState::CodeZeroHandShotChargeState()
    {
    
    }
    void CodeZeroHandShotChargeState::start()
    {
        m_body->noneResistanced();
    }
    void CodeZeroHandShotChargeState::update(double dt)
    {
        const s3d::Vec2 target = m_actor->isLeftHand() ? 
            m_parent->getPos() + s3d::Vec2{110, 0 }:
            m_parent->getPos() + s3d::Vec2{ -110, 0 };
        m_body->setPos(m_body->getPos().lerp(target, dt));

        const double rotateEnd = m_actor->isLeftHand() ? Math::ToRadians(40) : Math::ToRadians(-40);
        m_rotate->setRotate(s3d::EaseIn(s3d::Easing::Linear, m_rotate->getRotate(), rotateEnd, dt));
    }
}
