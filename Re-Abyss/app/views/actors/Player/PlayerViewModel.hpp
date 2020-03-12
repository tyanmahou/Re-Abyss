﻿#pragma once
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss
{
    struct PlayerViewModel
    {
        PlayerActor::Motion motion;
        s3d::Vec2 pos;
        s3d::Vec2 vellocity;
        Forward forward;
        s3d::int32 charge;
    };
}