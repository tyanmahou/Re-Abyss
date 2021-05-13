#pragma once
#include "EnemyEntity.hpp"

namespace abyss::Actor::Enemy
{
    struct RollingTakoEntity : EnemyEntity
    {
        bool wait;
    };
}