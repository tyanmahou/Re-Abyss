#pragma once
#include "GimmickEntity.hpp"
#include <abyss/types/Actor/Gimmick/BushKind.hpp>

namespace abyss::Actor::Gimmick
{
    struct BushEntity : GimmickEntity
    {
        BushKind kind;
    };
}