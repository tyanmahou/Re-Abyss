#include "BodyUpdater.hpp"
#include "Body.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    BodyUpdater::BodyUpdater(IActor* pActor):
        m_pActor(pActor)
    {}

    void BodyUpdater::setup()
    {
        m_body = m_pActor->find<Body>();
    }

    void BodyUpdater::onMove(double dt)
    {
        if (!m_isActive) {
            return;
        }
        if (!m_body) {
            return;
        }
        m_body->update(dt);
    }
}
