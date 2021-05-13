#pragma once
#include "GimmickEntity.hpp"
#include <Siv3D/String.hpp>

namespace abyss::Actor::Gimmick
{
    struct EventTriggerEntity : GimmickEntity
    {
        s3d::FilePath event;
    };
}