#include "TerrainModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

bool abyss::TerrainModel::isActive() const
{
    return m_isActive && m_pActor->isActive();
}
bool abyss::TerrainModel::accept(const ActVisitor& visit) const
{
    return m_pActor->accept(visit);
}
