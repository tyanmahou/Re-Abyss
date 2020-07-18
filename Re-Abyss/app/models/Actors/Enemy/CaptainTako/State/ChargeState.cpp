#include "ChargeState.hpp"
#include "AttackState.hpp"

#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::CaptainTako
{
    ChargeState::ChargeState()
    {}
    void ChargeState::start()
    {
        m_chargeTimer = ActorUtils::CreateTimer(*m_pActor, Param::Charge::TimeSec);
        m_pActor->find<AudioSourceModel>()->play(U"Charge");
        m_draw->request(DrawModel::Kind::Charge);
    }
    void ChargeState::update([[maybe_unused]]double dt)
    {
        if (m_chargeTimer.reachedZero()) {
            this->changeState<AttackState>();
        }

        m_draw->setChargeTime(m_chargeTimer.progress0_1());
    }
}
