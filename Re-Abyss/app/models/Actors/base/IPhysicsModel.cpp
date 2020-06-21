#include "IPhysicsModel.hpp"
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/MapColInfo.hpp>

bool abyss::IPhysicsModel::intersects(const MapColInfo& mapColInfo) const

{
    return this->getCollider().intersects(mapColInfo.region);
}