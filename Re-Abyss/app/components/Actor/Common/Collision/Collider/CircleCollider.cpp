#include "CircleCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D/Circle.hpp>
namespace abyss::Actor::Collision
{
    CircleCollider::CircleCollider(ActorObj* pActor, Ref<ILocator> locator) :
        m_pActor(pActor),
        m_locator(locator)
    {}
    void CircleCollider::onStart()
    {
        if (!m_locator) {
            m_locator = m_pActor->find<ILocator>();
        }
    }
    CShape CircleCollider::getCollider() const
    {
        return s3d::Circle(m_locator->getCenterPos(), m_radius);
    }
}
