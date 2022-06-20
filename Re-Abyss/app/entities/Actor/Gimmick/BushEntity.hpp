#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>

namespace abyss::Actor::Gimmick
{
    /// <summary>
    /// くさむら種類
    /// </summary>
    enum class BushKind
    {
        Left,
        Center,
        Right,

        Default = Center,
    };

    struct BushEntity : GimmickEntity
    {
        BushKind kind;
    };
}
