#include "ChargeState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/params/Actors/CaptainTako/Param.hpp>
namespace abyss::CaptainTako
{
    ChargeState::ChargeState():
        m_chargeTimer(Param::Charge::TimeSec, true, WorldTime::TimeMicroSec)
    {}
    void ChargeState::update(double dt)
    {
        if (m_chargeTimer.reachedZero()) {
            this->changeState(State::Attack);
        }
        BaseState::update(dt);
    }

    void ChargeState::draw() const
    {
        m_actor->getBindedView()->drawCharge(m_chargeTimer.progress0_1());
    }
}
