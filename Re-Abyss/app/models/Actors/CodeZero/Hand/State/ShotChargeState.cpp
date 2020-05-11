#include "ShotChargeState.hpp"
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <Siv3D.hpp>
namespace abyss::CodeZero::Hand
{
    ShotChargeState::ShotChargeState()
    {
    
    }
    void ShotChargeState::start()
    {
        m_body->noneResistanced();
    }
    void ShotChargeState::update(double dt)
    {
        const s3d::Vec2 target = m_pActor->isLeftHand() ? 
            m_parent->getPos() + s3d::Vec2{110, 0 }:
            m_parent->getPos() + s3d::Vec2{ -110, 0 };
        m_body->setPos(m_body->getPos().lerp(target, dt));

        const double rotateEnd = m_pActor->isLeftHand() ? Math::ToRadians(40) : Math::ToRadians(-40);
        m_rotate->setRotate(s3d::EaseIn(s3d::Easing::Linear, m_rotate->getRotate(), rotateEnd, dt));
    }
}
