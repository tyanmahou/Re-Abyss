#include <abyss/entities/Enemy/CaptainTakoEntity.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include "State/CaptainTakoWaitState.hpp"
#include "State/CaptainTakoChargeState.hpp"
#include "State/CaptainTakoAttackState.hpp"

namespace abyss
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_unique<CaptainTakoVM>())
    {
        m_hp.setHp(10);
        m_body.setSize({ 32, 38 }).setPivot({ 0, 1 });

        m_state
            .add<CaptainTakoWaitState>(State::Wait)
            .add<CaptainTakoChargeState>(State::Charge)
            .add<CaptainTakoAttackState>(State::Attack)
            .bind<BodyModel>(&CaptainTakoActor::m_body)
            ;
    }
    void CaptainTakoActor::update(double dt)
    {
        m_state.update(dt);
    }
    void CaptainTakoActor::draw() const
    {
        m_state.draw();
    }
    void CaptainTakoActor::onCollisionStay(ICollider * col)
    {
        m_state.onCollisionStay(col);
    }
    bool CaptainTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    CaptainTakoVM* CaptainTakoActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setForward(m_body.getForward())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
