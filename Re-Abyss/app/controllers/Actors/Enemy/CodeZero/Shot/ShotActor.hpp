#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

namespace abyss::Actor::CodeZero::Shot
{
    class ShotActor: 
        public IActor,
        public Attacker,
        public Receiver
    {
    public:
        ShotActor(IActor* parent);

        bool accept(const ActVisitor& visitor) override;
    };
}