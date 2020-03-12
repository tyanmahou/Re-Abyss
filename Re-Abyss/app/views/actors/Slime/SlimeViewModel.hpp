#pragma once
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>

namespace abyss
{
    struct SlimeViewModel
    {
        SlimeActor::Motion motion;
        Forward forward;
        s3d::Vec2 pos;
        s3d::Vec2 vellocity;
    };
}