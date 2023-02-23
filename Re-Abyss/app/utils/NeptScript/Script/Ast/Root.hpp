#pragma once
#include <abyss/utils/NeptScript/Script/Ast/IStatement.hpp>
#include <Siv3D/Array.hpp>
#include <memory>

namespace abyss::Nept::Ast
{
    struct Root : INode
    {
        s3d::Array<std::shared_ptr<IStatement>> statements;
    };
}
