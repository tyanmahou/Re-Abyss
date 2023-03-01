#pragma once
#include <abyss/utils/NeptScript/Ast/IStatement.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Nept::Ast
{
    struct TextStatement : IStatement
    {
        s3d::String text;
    };
}
