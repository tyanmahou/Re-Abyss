#include "CaptainTakoChargeState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>

namespace abyss
{
    CaptainTakoChargeState::CaptainTakoChargeState():
        m_chargeTimer(2.0, true, WorldTime::TimeMicroSec)
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
