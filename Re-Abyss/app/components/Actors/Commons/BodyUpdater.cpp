#include "BodyUpdater.hpp"
#include "Body.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss::Actor
{
    BodyUpdater::BodyUpdater(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void BodyUpdater::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void BodyUpdater::onMove()
    {
        if (!m_isActive) {
            return;
        }
        if (!m_body) {
            return;
        }
        m_body->update(m_pActor->deltaTime());
    }
}
