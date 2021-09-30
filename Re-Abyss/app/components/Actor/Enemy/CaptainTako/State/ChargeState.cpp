#include "ChargeState.hpp"
#include "AttackState.hpp"

#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    ChargeState::ChargeState():
        m_chargeTimer(Param::Charge::TimeSec)
    {}
    void ChargeState::start()
    {
        m_motion->set(Motion::Charge);
        m_charge->setRate(0);
    }
    Task<> ChargeState::task()
    {
        m_audio->play(U"Charge");

        while (!m_chargeTimer.isEnd()) {
            co_yield{};
        }
        this->changeState<AttackState>();
        co_return;
    }
    void ChargeState::update()
    {
        m_chargeTimer.update(m_pActor->deltaTime());

        m_charge->setRate(m_chargeTimer.rate());
    }
}
