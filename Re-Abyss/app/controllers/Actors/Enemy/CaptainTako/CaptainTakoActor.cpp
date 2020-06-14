#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/State/ChargeState.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/State/AttackState.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
namespace abyss::CaptainTako
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_unique<CaptainTakoVM>())
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setAudioSettingGroupPath(U"Enemy/CaptainTako/captain_tako.aase")
            .build();

        {
            this->attach<StateModel<CaptainTakoActor>>(this)
                ->add<WaitState>(State::Wait)
                .add<ChargeState>(State::Charge)
                .add<AttackState>(State::Attack)
                ;
        }
    }
    bool CaptainTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    CaptainTakoVM* CaptainTakoActor::getBindedView() const
    {
        return &m_view
            ->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
