#include <abyss/components/Actor/Enemy/CaptainTako/State/ChargeState.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/State/AttackState.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/SeDef.hpp>
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
    Fiber<> ChargeState::updateAsync()
    {
        m_audio->play(SeDef::Charge);

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
