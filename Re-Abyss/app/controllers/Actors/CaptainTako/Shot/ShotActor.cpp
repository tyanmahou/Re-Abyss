#include "State/BaseState.hpp"
#include <abyss/views/Actors/CaptainTako/Shot/ShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CaptainTako/ShotParam.hpp>

namespace abyss::CaptainTako::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward):
        m_state(this),
        m_view(std::make_shared<ShotVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state
            .add<BaseState>(State::Base)
            .bind<BodyModel>(&ShotActor::m_body);

        m_body
            .setPos(pos)
            .setForward(forward)
            .noneResistanced()
            .setVelocityX(forward * ShotParam::Base::Speed)
            ;
        m_power = 1;
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
        return this->getColliderCircle();
    }

    void ShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }

    s3d::Circle ShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body.getPos(), ShotParam::Base::ColRadius);
    }

    bool ShotActor::accept(const ActVisitor& visitor)
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
            ->setPos(m_body.getPos())
            .setForward(m_body.getForward());
    }

}
