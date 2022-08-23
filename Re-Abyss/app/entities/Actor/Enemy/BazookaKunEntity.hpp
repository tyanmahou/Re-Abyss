#pragma once
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>

namespace abyss::Actor::Enemy
{
    struct BazookaKunEntity : EnemyEntity
    {
        bool isMirrored;
        bool isFlipped;
        double rotate;

        bool isFixBazooka;
        double bazookaRotate;
    };
}
