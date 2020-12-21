#include "Terrain.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    bool Terrain::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
}
