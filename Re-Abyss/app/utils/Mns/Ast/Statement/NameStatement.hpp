#pragma once
#include "../IStatement.hpp"
#include <Siv3D/String.hpp>

namespace Mns::Ast
{
    struct NameStatement : IStatement
    {
        s3d::String name;
    };
}