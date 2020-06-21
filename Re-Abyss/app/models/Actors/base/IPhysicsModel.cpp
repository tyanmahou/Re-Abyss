#include "IPhysicsModel.hpp"
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/MapColInfo.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
    bool IPhysicsModel::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    bool IPhysicsModel::intersects(const MapColInfo& mapColInfo) const
    {
        return this->getCollider().intersects(mapColInfo.region);
    }
}
