#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    ShotChargeState::ShotChargeState()
    {
    
    }
    void ShotChargeState::start()
    {
        m_handMove->startForShotCharge();
    }
    void ShotChargeState::update()
    {
    }
}
