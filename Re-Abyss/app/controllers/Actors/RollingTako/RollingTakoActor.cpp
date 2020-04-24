#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/Param.hpp>
#include "State/WaitState.hpp"
#include "State/RunState.hpp"

namespace abyss::RollingTako
{
    RollingTakoActor::RollingTakoActor(const RollingTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_isWait(entity.wait),
        m_state(this),
        m_view(std::make_unique<RollingTakoVM>())
    {
        m_hp.setHp(Param::Base::Hp);
        m_body
            .setSize(Param::Base::Size)
            .setPivot(Param::Base::Pivot)
            .setMaxSpeedX(Param::Run::MaxSpeedX);

        m_state
            .add<WaitState>(State::Wait)
            .add<RunState>(State::Run)
            .bind<BodyModel>(&RollingTakoActor::m_body)
        ;
        if (!m_isWait) {
            m_state.changeState(State::Run);
        }
    }
    void RollingTakoActor::update(double dt)
    {
        m_state.update(dt);
    }
    void RollingTakoActor::lastUpdate(double dt)
    {
        m_state.lastUpdate(dt);
    }
    void RollingTakoActor::draw() const
    {
        m_state.draw();
    }
    void RollingTakoActor::onCollisionStay(ICollider * col)
    {
        m_state.onCollisionStay(col);
    }
    bool RollingTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    RollingTakoVM* RollingTakoActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setForward(m_body.getForward())
            .setIsDamaging(m_hp.isInInvincibleTime())
            ;
    }
}
