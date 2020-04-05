#include "State/LaunSharkShotWaitState.hpp"
#include "State/LaunSharkShotPursuitState.hpp"
#include "State/LaunSharkShotFiringedState.hpp"
#include <abyss/commons/LayerGroup.hpp>
#include <Siv3D/MathConstants.hpp>

namespace abyss
{
    LaunSharkShotActor::LaunSharkShotActor(const s3d::Vec2& pos, Forward forward):
        m_state(this),
        m_view(std::make_shared<LaunSharkShotVM>())
    {
        if (forward == Forward::Right) {
            m_rotate.setRotate(s3d::Math::Constants::Pi);
        }
        this->layer = LayerGroup::Enemy;
        m_body
            .setPos(pos)
            .noneResistanced()
            .setSize({30, 10});
        m_hp.setHp(4).setInvincibleTime(0.2);
        m_state
            .add<LaunSharkShotWaitState>(State::Wait)
            .add<LaunSharkShotPursuitState>(State::Pursuit)
            .add<LaunSharkShotFiringedState>(State::Firinged)
            .bind<BodyModel>(&LaunSharkShotActor::m_body)
            .bind<HPModel>(&LaunSharkShotActor::m_hp)
            .bind<RotateModel>(&LaunSharkShotActor::m_rotate)
            ;
    }
    void LaunSharkShotActor::start()
    {    
    }
    void LaunSharkShotActor::update(double dt)
    {
        m_state.update(dt);
    }
    CShape LaunSharkShotActor::getCollider() const
    {
        return this->getColliderQuad();
    }
    void LaunSharkShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    s3d::Quad LaunSharkShotActor::getColliderQuad() const
    {
        return m_body.region().rotated(m_rotate.getRotate());
    }
    bool LaunSharkShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
    void LaunSharkShotActor::draw() const
    {
        m_state.draw();
    }

    LaunSharkShotVM* LaunSharkShotActor::getBindedView() const
    {
        return &(*m_view)
            .setPos(m_body.getPos())
            .setRotate(m_rotate.getRotate())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
