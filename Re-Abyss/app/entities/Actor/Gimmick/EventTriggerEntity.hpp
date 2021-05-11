#pragma once
#include "GimmickEntity.hpp"
#include <Siv3D/String.hpp>

namespace abyss
{
    struct EventTriggerEntity : GimmickEntity
    {
        s3d::FilePath event;
    };
}