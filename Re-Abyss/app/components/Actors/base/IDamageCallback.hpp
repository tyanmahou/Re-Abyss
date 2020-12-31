#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    struct DamageData
    {
        s3d::int32 damage;
        s3d::Vec2 velocity;
    };

    class IDamageCallback
    { 
    public:
        virtual ~IDamageCallback() = default;
        virtual void onDamaged(const DamageData& damage) = 0;
    };
}