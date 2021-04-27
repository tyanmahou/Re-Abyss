#include "Terrain.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss::Actor
{
    bool Terrain::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
}
