#pragma once
#include "GimmickEntity.hpp"

namespace abyss
{
    struct StartPosEntity : GimmickEntity
    { 
        s3d::int32 startId;
        Forward forward;
        bool isSave;
    };
}