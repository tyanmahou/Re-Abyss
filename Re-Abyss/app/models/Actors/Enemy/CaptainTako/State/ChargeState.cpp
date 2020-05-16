#include "ChargeState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/controllers/Sound/Sound.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
namespace abyss::CaptainTako
{
    ChargeState::ChargeState()
    {}
    void ChargeState::start()
    {
        m_chargeTimer = ActorUtils::CreateTimer(*m_pActor, Param::Charge::TimeSec);
        m_pActor->find<AudioSourceModel>()->play(U"Enemy/CaptainTako/charge.ogg");
    }
    void ChargeState::update(double dt)
    {
        if (m_chargeTimer.reachedZero()) {
            this->changeState(State::Attack);
        }
        BaseState::update(dt);
    }

    void ChargeState::draw() const
    {
        m_pActor->getBindedView()->drawCharge(m_chargeTimer.progress0_1());
    }
}
