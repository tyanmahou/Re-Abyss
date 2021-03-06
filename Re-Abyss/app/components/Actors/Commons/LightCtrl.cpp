#include "LightCtrl.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/System/System.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor
{
    LightCtrl::LightCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void LightCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void LightCtrl::onDraw() const
    {
        auto pos = m_body->getPos();
        m_pActor->getModule<Light>()->addLight({ pos, m_radius, m_brightness });
    }
}
