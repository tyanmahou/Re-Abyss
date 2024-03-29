#pragma once
#include <abyss/utils/NeptScript/Ast/IStatement.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Nept::Ast
{
    enum class LookType
    {
        Left,
        Right,
        Center,
    };
    struct CharaStatement : IStatement
    {
        LookType look;
        s3d::String actor;
        s3d::Optional<s3d::String> emote;
        s3d::Optional<s3d::String> displayName;
    };
}
