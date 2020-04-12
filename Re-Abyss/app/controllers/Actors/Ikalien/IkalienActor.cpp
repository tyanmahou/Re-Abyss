#include "State/IkalienPursuitState.hpp"
#include "State/IkalienSwimState.hpp"
#include "State/IkalienWaitState.hpp"
#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/params/Actors/Ikalien/IkalienParam.hpp>

namespace abyss
{
    IkalienActor::IkalienActor(const IkalienEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<IkalienVM>())
    {
        m_hp.setHp(IkalienParam::Base::Hp);
        m_body.noneResistanced().setPivot(IkalienParam::Base::Pivot);

        m_state
            .add<IkalienWaitState>(State::Wait)
            .add<IkalienPursuitState>(State::Pursuit)
            .add<IkalienSwimState>(State::Swim)
            .bind<BodyModel>(&IkalienActor::m_body)
            .bind<RotateModel>(&IkalienActor::m_rotate)
            ;
    }
    void IkalienActor::update(double dt)
    {
        m_state.update(dt);
    }
    void IkalienActor::draw() const
    {
        m_state.draw();
    }
    CShape IkalienActor::getCollider() const
    {
        return s3d::Circle(m_body.getPivotPos(), IkalienParam::Base::ColRadius);
    }
    void IkalienActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool IkalienActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    IkalienVM* IkalienActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setVelocity(m_body.getVelocity())
            .setRotate(m_rotate.getRotate())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
