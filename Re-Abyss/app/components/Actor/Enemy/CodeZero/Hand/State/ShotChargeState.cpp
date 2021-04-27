#include "ShotChargeState.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    ShotChargeState::ShotChargeState()
    {
    
    }
    Task<> ShotChargeState::start()
    {
        m_body->noneResistanced()
            .setVelocity(s3d::Vec2::Zero());
        co_return;
    }
    void ShotChargeState::update()
    {
        auto dt = m_pActor->deltaTime();

        const s3d::Vec2 target = m_kind->isLeftHand() ? 
            m_parent->getPos() + s3d::Vec2{110, 0 }:
            m_parent->getPos() + s3d::Vec2{ -110, 0 };
        m_body->setPos(m_body->getPos().lerp(target, dt));

        const double rotateEnd = m_kind->isLeftHand() ? Math::ToRadians(40) : Math::ToRadians(-40);
        m_rotate->setRotate(s3d::EaseIn(s3d::Easing::Linear, m_rotate->getRotate(), rotateEnd, dt));
    }
}
