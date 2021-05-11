#pragma once
#include <abyss/entities/Actor/Item/ItemEntity.hpp>

namespace abyss::Actor::Item
{
    enum class RecoveryKind
    {
        Small,
        Big,
    };
    struct RecoveryEntity : ItemEntity
    {
        RecoveryKind kind;
    };
}