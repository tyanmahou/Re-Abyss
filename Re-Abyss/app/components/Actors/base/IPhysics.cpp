#include "IPhysics.hpp"
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/MapColInfo.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/types/CShape.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Actor
{
    bool IPhysics::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    bool IPhysics::intersects(const MapColInfo& mapColInfo) const
    {
        return ColisionUtil::Intersects(this->getCollider(), mapColInfo.region);
    }
}
