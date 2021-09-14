#include "LightCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor
{
    LightCtrl::LightCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void LightCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void LightCtrl::onDraw() const
    {
        auto pos = m_body->getPos();
        m_pActor->getModule<Light>()->addCircle(pos, m_radius, m_brightness);
    }
}
