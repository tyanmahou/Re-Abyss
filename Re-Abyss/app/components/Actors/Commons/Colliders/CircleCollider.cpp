#include "CircleCollider.hpp"
#include <Siv3D/Circle.hpp>

namespace abyss::Actor
{
    CircleCollider::CircleCollider(IActor* pActor):
        m_pActor(pActor)
    {}
    void CircleCollider::onStart()
    {
        m_locator = m_pActor->find<ILocator>();
    }
    CShape CircleCollider::getCollider() const
    {
        return s3d::Circle(m_locator->getCenterPos(), m_radius);
    }
}
