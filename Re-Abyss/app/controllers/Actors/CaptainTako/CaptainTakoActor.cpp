#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/models/Actors/CaptainTako/State/WaitState.hpp>
#include <abyss/models/Actors/CaptainTako/State/ChargeState.hpp>
#include <abyss/models/Actors/CaptainTako/State/AttackState.hpp>
#include <abyss/params/Actors/CaptainTako/Param.hpp>

#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>
namespace abyss::CaptainTako
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_unique<CaptainTakoVM>())
    {
        {
            m_hp
                ->setHp(Param::Base::Hp);
        }
        {
            m_body
                ->setSize(Param::Base::Size).setPivot(Param::Base::Pivot);
        }

        {
            this->attach<exp::StateModel<CaptainTakoActor>>(this)
                ->add<WaitState>(State::Wait)
                .add<ChargeState>(State::Charge)
                .add<AttackState>(State::Attack)
                ;
        }
        {
            this->attach<DamageModel>(this);
            this->attach<Enemy::DeadCallbackModel>(this);
        }
    }
    bool CaptainTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    CaptainTakoVM* CaptainTakoActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
