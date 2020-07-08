#include "GodActor.hpp"
#include <abyss/models/Actors/God/PauseModel.hpp>

namespace abyss::God
{
    GodActor::GodActor()
    {
        this->m_isDontDestoryOnLoad = true;
        this->attach<PauseModel>(this);
    }
}
