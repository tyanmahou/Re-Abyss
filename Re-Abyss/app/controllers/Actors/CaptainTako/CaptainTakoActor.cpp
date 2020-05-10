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
            m_hpModel
                ->setHp(Param::Base::Hp);
        }
        {
            m_bodyModel
                ->setSize(Param::Base::Size).setPivot(Param::Base::Pivot);
        }

        {
            this->addComponent<exp::StateModel<CaptainTakoActor>>(this)
                ->add<WaitState>(State::Wait)
                .add<ChargeState>(State::Charge)
                .add<AttackState>(State::Attack)
                ;
        }
        {
            this->addComponent<DamageModel>(this);
            this->addComponent<Enemy::DeadCallbackModel>(this);
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
            .setIsDamaging(m_hpModel->isInInvincibleTime());
    }
}
