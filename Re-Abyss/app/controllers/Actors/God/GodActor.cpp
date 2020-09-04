#include "GodActor.hpp"
#include <abyss/components/Actors/God/PauseCtrl.hpp>

namespace abyss::Actor::God
{
    GodActor::GodActor()
    {
        this->m_isDontDestoryOnLoad = true;
        this->attach<PauseCtrl>(this);
    }
}
