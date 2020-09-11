#include "IPhysics.hpp"
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/MapColInfo.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    bool IPhysics::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    bool IPhysics::intersects(const MapColInfo& mapColInfo) const
    {
        return this->getCollider().intersects(mapColInfo.region);
    }
}
