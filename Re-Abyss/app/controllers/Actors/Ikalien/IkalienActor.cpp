#include "State/PursuitState.hpp"
#include "State/SwimState.hpp"
#include "State/WaitState.hpp"
#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/params/Actors/Ikalien/Param.hpp>

namespace abyss::Ikalien
{
    IkalienActor::IkalienActor(const IkalienEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<IkalienVM>())
    {
        m_hp.setHp(Param::Base::Hp);
        m_body.noneResistanced().setPivot(Param::Base::Pivot);

        m_state
            .add<WaitState>(State::Wait)
            .add<PursuitState>(State::Pursuit)
            .add<SwimState>(State::Swim)
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
        return s3d::Circle(m_body.getPivotPos(), Param::Base::ColRadius);
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
