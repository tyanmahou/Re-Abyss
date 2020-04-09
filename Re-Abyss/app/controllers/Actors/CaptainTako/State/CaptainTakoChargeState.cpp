#include "CaptainTakoChargeState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/params/Actors/CaptainTako/CaptainTakoParam.hpp>
namespace abyss
{
    CaptainTakoChargeState::CaptainTakoChargeState():
        m_chargeTimer(CaptainTakoParam::Charge::TimeSec, true, WorldTime::TimeMicroSec)
    {}
    void CaptainTakoChargeState::update(double dt)
    {
        if (m_chargeTimer.reachedZero()) {
            this->changeState(CaptainTakoActor::State::Attack);
        }
        CaptainTakoBaseState::update(dt);
    }

    void CaptainTakoChargeState::draw() const
    {
        m_actor->getBindedView()->drawCharge(m_chargeTimer.progress0_1());
    }
}
