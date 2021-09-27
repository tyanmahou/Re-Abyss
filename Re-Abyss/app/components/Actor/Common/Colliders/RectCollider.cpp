#include "RectCollider.hpp"
#include <Siv3D/RectF.hpp>

namespace abyss::Actor
{
    RectCollider::RectCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void RectCollider::onStart()
    {
        m_locator = m_pActor->find<ILocator>();
    }
    CShape RectCollider::getCollider() const
    {
        return s3d::RectF(s3d::Arg::center = m_locator->getCenterPos() + m_offset, m_size);
    }
}
