#pragma once
#include <abyss/utils/Mns/Ast/IStatement.hpp>
#include <Siv3D/String.hpp>

namespace Mns::Ast
{
    struct TextStatement : IStatement
    {
        s3d::String text;
    };
}