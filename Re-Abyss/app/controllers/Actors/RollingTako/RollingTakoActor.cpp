#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/Param.hpp>
#include <abyss/models/Actors/RollingTako/State/WaitState.hpp>
#include <abyss/models/Actors/RollingTako/State/RunState.hpp>

#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>

namespace abyss::RollingTako
{
    RollingTakoActor::RollingTakoActor(const RollingTakoEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_isWait(entity.wait),
        m_view(std::make_unique<RollingTakoVM>())
    {
        {
            m_hp->setHp(Param::Base::Hp);
        }
        {
            m_body
                ->setSize(Param::Base::Size)
                .setPivot(Param::Base::Pivot)
                .setMaxSpeedX(Param::Run::MaxSpeedX);
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
        this->attach<DamageModel>(this);
        this->attach<Enemy::DeadCallbackModel>(this);
    }

    bool RollingTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    RollingTakoVM* RollingTakoActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime())
            ;
    }
}
