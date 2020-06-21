#include <abyss/models/Actors/Enemy/LaunShark/State/SwimState.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/State/AttackState.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/State/LauncherState.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
namespace abyss::LaunShark
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity):
        m_view(std::make_shared<LaunSharkVM>())
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true, true)
            .setAudioSettingGroupPath(U"Enemy/LaunShark/laun_shark.aase")
            .build();

        {
            m_body
                ->noneResistanced();
        }
        {
            this->attach<StateModel<LaunSharkActor>>(this)
                ->add<SwimState>(State::Swim)
                .add<LauncherState>(State::Launcher)
                .add<AttackState>(State::Attack)
                ;
        }
        {
            this->attach<TimeCounterModel>();
        }
    }
    
    bool LaunSharkActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    LaunSharkVM* LaunSharkActor::getBindedView() const
    {
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
