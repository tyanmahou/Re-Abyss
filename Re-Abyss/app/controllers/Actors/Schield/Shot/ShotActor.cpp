#include "State/BaseState.hpp"
#include <abyss/views/Actors/Schield/Shot/ShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/Schield/ShotParam.hpp>

namespace abyss::Schield::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir) :
        m_state(this),
        m_view(std::make_shared<ShotVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state
            .add<BaseState>(State::Base)
            .bind<BodyModel>(&ShotActor::m_body);

        m_body
            .setPos(pos)
            .noneResistanced()
            .setVelocity(dir.normalized() * ShotParam::Base::Speed);
        m_power = 1;
    }
    void ShotActor::update(double dt)
    {
        m_state.update(dt);
    }
    CShape ShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }
    s3d::Circle ShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body.getPos(), ShotParam::Base::ColRadius);
    }
    void ShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool ShotActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }
    void ShotActor::draw() const
    {
        m_state.draw();
    }
    ShotVM* ShotActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body.getPos());
    }
}
