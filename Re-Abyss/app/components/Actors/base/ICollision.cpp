#include "ICollision.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Actor
{
    bool ICollision::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }

    ICollision& ICollision::setLayer(s3d::int32 layer)
    {
        m_layer = layer;
        return *this;
    }

    s3d::int32 ICollision::getLayer() const
    {
        return m_layer;
    }

    s3d::uint64 ICollision::getId() const
    {
        return m_pActor->getId();
    }

    bool ICollision::intersects(const CShape& other) const
    {
        return ColisionUtil::Intersects(this->getCollider(), other);
    }

}
