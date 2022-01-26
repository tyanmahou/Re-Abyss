#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>

namespace abyss::Actor::Gimmick
{
    struct StartPosEntity : GimmickEntity
    { 
        s3d::int32 startId;
        Forward forward;
        bool isSave;
    };
}