#include "RectCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D/RectF.hpp>

namespace abyss::Actor::Collision
{
    RectCollider::RectCollider(ActorObj* pActor, Ref<ILocator> locator) :
        m_pActor(pActor)
    {}
    void RectCollider::onStart()
    {
        if (!m_locator) {
            m_locator = m_pActor->find<ILocator>();
        }
    }
    CShape RectCollider::getCollider() const
    {
        return s3d::RectF(s3d::Arg::center = m_locator->getCenterPos() + m_offset, m_size);
    }
}
