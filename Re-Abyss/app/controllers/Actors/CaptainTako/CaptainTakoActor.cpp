#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include "State/WaitState.hpp"
#include "State/ChargeState.hpp"
#include "State/AttackState.hpp"
#include <abyss/params/Actors/CaptainTako/Param.hpp>

namespace abyss::CaptainTako
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_unique<CaptainTakoVM>())
    {
        m_hp.setHp(Param::Base::Hp);
        m_body.setSize(Param::Base::Size).setPivot(Param::Base::Pivot);

        m_state
            .add<WaitState>(State::Wait)
            .add<ChargeState>(State::Charge)
            .add<AttackState>(State::Attack)
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
