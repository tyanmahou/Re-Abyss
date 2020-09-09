#include "ChargeState.hpp"
#include "AttackState.hpp"

#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    ChargeState::ChargeState()
    {}
    void ChargeState::start()
    {
        m_chargeTimer = ActorUtils::CreateTimer(*m_pActor, Param::Charge::TimeSec);
        m_pActor->find<AudioSource>()->play(U"Charge");
    }
    void ChargeState::update([[maybe_unused]]double dt)
    {
        if (m_chargeTimer.reachedZero()) {
            this->changeState<AttackState>();
        }
    }
    void ChargeState::draw() const
    {
        (*m_view)->drawCharge(m_chargeTimer.progress0_1());
    }
}
