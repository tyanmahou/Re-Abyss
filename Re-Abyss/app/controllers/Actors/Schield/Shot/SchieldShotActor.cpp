#include "State/SchieldShotBaseState.hpp"
#include <abyss/views/Actors/Schield/Shot/SchieldShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/Schield/SchieldShotParam.hpp>

namespace abyss
{
    SchieldShotActor::SchieldShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir) :
        m_state(this),
        m_view(std::make_shared<SchieldShotVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state
            .add<SchieldShotBaseState>(State::Base)
            .bind<BodyModel>(&SchieldShotActor::m_body);

        m_body
            .setPos(pos)
            .noneResistanced()
            .setVelocity(dir.normalized() * SchieldShotParam::Base::Speed);
        m_power = 1;
    }
    void SchieldShotActor::update(double dt)
    {
        m_state.update(dt);
    }
    CShape SchieldShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }
    s3d::Circle SchieldShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body.getPos(), SchieldShotParam::Base::ColRadius);
    }
    void SchieldShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool SchieldShotActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }
    void SchieldShotActor::draw() const
    {
        m_state.draw();
    }
    SchieldShotVM* SchieldShotActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body.getPos());
    }
}
