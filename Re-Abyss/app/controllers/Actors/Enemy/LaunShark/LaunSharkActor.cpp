#include <abyss/models/Actors/Enemy/LaunShark/State/SwimState.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/State/AttackState.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/State/LauncherState.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>

namespace abyss::LaunShark
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_shared<LaunSharkVM>())
    {
        m_hp->setHp(Param::Base::Hp);
        m_body
            ->noneResistanced()
            .setSize(Param::Base::Size);
        this->attach<StateModel<LaunSharkActor>>(this)
            ->add<SwimState>(State::Swim)
            .add<LauncherState>(State::Launcher)
            .add<AttackState>(State::Attack)
            ;
        this->attach<TimeCounterModel>();
        this->attach<DamageModel>(this);
        this->attach<Enemy::DeadCallbackModel>(this);
    }
    
    bool LaunSharkActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    LaunSharkVM* LaunSharkActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
