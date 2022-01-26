#include <abyss/components/Actor/Common/Col/Collider/PointCollider.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Col
{
    PointCollider::PointCollider(ActorObj* pActor, Ref<ILocator> locator):
        m_pActor(pActor),
        m_locator(locator)
    {}
    void PointCollider::onStart()
    {
        if (!m_locator) {
            m_locator = m_pActor->find<ILocator>();
        }
    }
}
