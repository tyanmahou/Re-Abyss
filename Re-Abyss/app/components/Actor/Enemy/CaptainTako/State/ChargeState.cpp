#include "ChargeState.hpp"
#include "AttackState.hpp"

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    ChargeState::ChargeState()
    {}
    void ChargeState::start()
    {
        m_motion->set(Motion::Charge);
        m_charge->setRate(0);
    }
    Task<> ChargeState::task()
    {
        m_chargeTimer = ActorUtils::CreateTimer(*m_pActor, Param::Charge::TimeSec);
        m_audio->play(U"Charge");

        while (!m_chargeTimer.reachedZero()) {
            co_yield{};
        }
        this->changeState<AttackState>();
        co_return;
    }
    void ChargeState::update()
    {
        m_charge->setRate(m_chargeTimer.progress0_1());
    }
}
