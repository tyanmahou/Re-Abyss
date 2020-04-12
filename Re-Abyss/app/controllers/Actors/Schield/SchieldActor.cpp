#include "State/SchieldWaitState.hpp"
#include "State/SchieldAttackPlusState.hpp"
#include "State/SchieldAttackCrossState.hpp"

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/SchieldParam.hpp>
namespace abyss
{
    SchieldActor::SchieldActor(const SchieldEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<SchieldVM>())
    {
        m_state
            .add<SchieldWaitState>(State::Wait)
            .add<SchieldAttackPlusState>(State::AttackPlus)
            .add<SchieldAttackCrossState>(State::AttackCross)
            .bind<BodyModel>(&SchieldActor::m_body)
        ;
        m_body.setSize(SchieldParam::Base::Size);
        m_hp.setHp(SchieldParam::Base::Hp);
    }
    void SchieldActor::update(double dt)
    {
        m_state.update(dt);
    }
    void SchieldActor::draw() const
    {
        m_state.draw();
    }
    s3d::Circle SchieldActor::getFaceCollider() const
    {
        s3d::Vec2 offset{ 53.0 * m_body.getForward(), 16};
        return s3d::Circle(m_body.getPos() + offset, SchieldParam::Wait::FaceColRadius);
    }
    CShape SchieldActor::getCollider() const
    {
        if (m_state.getState() == State::Wait) {
            s3d::Array<CShape> shapes;
            shapes << this->getFaceCollider() << m_body.region();
            return shapes;
        }
        return m_body.region();
    }
    void SchieldActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool SchieldActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    SchieldVM* SchieldActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setForward(m_body.getForward())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
