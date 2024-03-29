#pragma once
#include <abyss/entities/Actor/Item/ItemEntity.hpp>

namespace abyss::Actor::Item
{
    enum class RecoveryKind
    {
        None,
        Small,
        Middle,
        Big,

        Default = Small,
    };
    struct RecoveryEntity : ItemEntity
    {
        RecoveryKind kind;
    };
}