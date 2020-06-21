#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/views/Actors/Enemy/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/RunState.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
namespace abyss::RollingTako
{
    RollingTakoActor::RollingTakoActor(const RollingTakoEntity& entity):
        m_isWait(entity.wait),
        m_view(std::make_unique<RollingTakoVM>())
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true)
            .setAudioSettingGroupPath(U"Enemy/RollingTako/rolling_tako.aase")
            .build();

        {
            m_body->setMaxSpeedX(Param::Run::MaxSpeedX);
        }
        {
            (m_state = this->attach<StateModel<RollingTakoActor>>(this))
                ->add<WaitState>(State::Wait)
                .add<RunState>(State::Run)
            ;
            if (!m_isWait) {
                m_state->changeState(State::Run);
            }
        }
    }

    bool RollingTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    RollingTakoVM* RollingTakoActor::getBindedView() const
    {
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime())
            ;
    }
}
