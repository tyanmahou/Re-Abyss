#pragma once
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>

namespace abyss::Actor::Ooparts::Nyan
{
    class NyanActor :
        public OopartsActor
    {
    public:
        NyanActor(IActor* parent);
    };
}