#include <abyss/entities/Enemy/RollingTakoEntity.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>

#include "State/RollingTakoWaitState.hpp"
#include "State/RollingTakoRunState.hpp"

namespace abyss
{
    RollingTakoActor::RollingTakoActor(const RollingTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_isWait(entity.wait),
        m_state(this),
        m_view(std::make_unique<RollingTakoVM>())
    {
        m_hp.setHp(6);
        m_body
            .setSize({45, 45})
            .setPivot({0, 7.5})
            .setMaxSpeedX(200);

        m_state
            .add<RollingTakoWaitState>(State::Wait)
            .add<RollingTakoRunState>(State::Run)
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
