#pragma once
#include <abyss/utils/NeptScript/Ast/IStatement.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Nept::Ast
{
    using CommandParam = std::pair<s3d::String, s3d::Optional<s3d::String>>;

    struct CommandStatement : IStatement
    {
        s3d::String command;
        s3d::Optional<s3d::String> rootParam;
        s3d::Array<CommandParam> params;
    };
}
