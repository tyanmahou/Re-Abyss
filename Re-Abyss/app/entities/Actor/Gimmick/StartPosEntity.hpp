#pragma once
#include "GimmickEntity.hpp"

namespace abyss::Actor::Gimmick
{
    struct StartPosEntity : GimmickEntity
    { 
        s3d::int32 startId;
        Forward forward;
        bool isSave;
    };
}