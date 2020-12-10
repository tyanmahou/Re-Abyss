#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class ShotActor: 
        public IActor,
        public Receiver
    {
    public:
        ShotActor(IActor* parent);

        bool accept(const ActVisitor& visitor) override;
    };
}