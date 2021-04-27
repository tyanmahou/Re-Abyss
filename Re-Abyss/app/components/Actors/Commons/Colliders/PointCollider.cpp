#include "PointCollider.hpp"

namespace abyss::Actor
{
    PointCollider::PointCollider(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void PointCollider::onStart()
    {
        m_locator = m_pActor->find<ILocator>();
    }
}
