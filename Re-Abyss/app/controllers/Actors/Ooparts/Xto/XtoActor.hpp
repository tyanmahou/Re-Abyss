#pragma once
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>

namespace abyss::Ooparts::Xto
{
    class XtoActor :
        public OopartsActor
    {
    public:
        XtoActor(IActor* parent);
    };
}