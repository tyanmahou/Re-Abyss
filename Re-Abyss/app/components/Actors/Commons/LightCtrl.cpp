#include "LightCtrl.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor
{
    LightCtrl::LightCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void LightCtrl::setup()
    {
        m_body = m_pActor->find<Body>();
    }

    void LightCtrl::onDraw() const
    {
        auto pos = m_body->getPos();
        m_pActor->getModule<Light>()->addLight({ pos, m_radius, m_brightness });
    }
}
