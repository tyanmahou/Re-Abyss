#include "ChargeState.hpp"
#include "AttackState.hpp"

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    ChargeState::ChargeState()
    {}
    Task<> ChargeState::task()
    {
        m_chargeTimer = ActorUtils::CreateTimer(*m_pActor, Param::Charge::TimeSec);
        m_pActor->find<AudioSource>()->play(U"Charge");

        while (!m_chargeTimer.reachedZero()) {
            co_yield{};
        }
        this->changeState<AttackState>();
        co_return;
    }
    void ChargeState::update()
    {
    }
    void ChargeState::draw() const
    {
        (*m_view)->drawCharge(m_chargeTimer.progress0_1());
    }
}
