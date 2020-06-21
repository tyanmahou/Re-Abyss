#include "TerrainModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

bool abyss::TerrainModel::accept(const ActVisitor& visit) const
{
    return m_pActor->accept(visit);
}
