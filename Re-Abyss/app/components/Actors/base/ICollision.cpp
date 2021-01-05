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

    ICollision& ICollision::setToLayer([[maybe_unused]]s3d::None_t none)
    {
        m_toLayer = s3d::none;
        return *this;
    }

    ICollision& ICollision::setToLayer(s3d::int32 toLayer)
    {
        m_toLayer = toLayer;
        return *this;
    }

    s3d::int32 ICollision::getToLayer() const
    {
        return m_toLayer.value_or(~m_layer);
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
