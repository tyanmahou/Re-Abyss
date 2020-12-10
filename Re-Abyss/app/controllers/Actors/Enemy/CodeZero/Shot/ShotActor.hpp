#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class ShotActor: 
        public IActor
    {
    public:
        ShotActor(IActor* parent);

        bool accept(const ActVisitor& visitor) override;
    };
}