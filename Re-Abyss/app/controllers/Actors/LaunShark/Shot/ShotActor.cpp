#include "State/WaitState.hpp"
#include "State/PursuitState.hpp"
#include "State/FiringedState.hpp"
#include <abyss/commons/LayerGroup.hpp>
#include <Siv3D/MathConstants.hpp>
#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward):
        m_state(this),
        m_view(std::make_shared<ShotVM>())
    {
        if (forward == Forward::Right) {
            m_rotate.setRotate(s3d::Math::Constants::Pi);
        }
        this->layer = LayerGroup::Enemy;
        m_body
            .setPos(pos)
            .noneResistanced()
            .setSize(ShotParam::Base::Size);
        m_hp.setHp(ShotParam::Base::Hp).setInvincibleTime(0.2);
        m_state
            .add<WaitState>(State::Wait)
            .add<PursuitState>(State::Pursuit)
            .add<FiringedState>(State::Firinged)
            .bind<BodyModel>(&ShotActor::m_body)
            .bind<HPModel>(&ShotActor::m_hp)
            .bind<RotateModel>(&ShotActor::m_rotate)
            ;
    }
    void ShotActor::start()
    {    
    }
    void ShotActor::update(double dt)
    {
        m_state.update(dt);
    }
    CShape ShotActor::getCollider() const
    {
        return this->getColliderQuad();
    }
    void ShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    s3d::Quad ShotActor::getColliderQuad() const
    {
        return m_body.region().rotated(m_rotate.getRotate());
    }
    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
    void ShotActor::draw() const
    {
        m_state.draw();
    }

    ShotVM* ShotActor::getBindedView() const
    {
        return &(*m_view)
            .setPos(m_body.getPos())
            .setRotate(m_rotate.getRotate())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
