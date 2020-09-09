#include "Terrain.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    bool Terrain::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    bool Terrain::accept(const ActVisitor& visit) const
    {
        return m_pActor->accept(visit);
    }

}
