#include "SenserCtrl.hpp"
#include <abyss/components/Actors/Enemy/Slime/Sensor/Builder.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss::Actor::Enemy::Slime
{
    SenserCtrl::SenserCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    void SenserCtrl::onStart()
    {
        m_senser = m_pActor->getModule<World>()->create<Sensor::Builder>(m_pActor);
    }

    void SenserCtrl::destroy()
    {
        if (m_senser) {
            m_senser->destroy();
        }
    }
}
