#pragma once
#include <abyss/utils/NeptScript/Ast/IStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/BlockStatement.hpp>
#include <Siv3D/String.hpp>
#include <memory>

namespace abyss::Nept::Ast
{
    struct SectionStatement : IStatement
    {
        s3d::String section;
        std::shared_ptr<BlockStatement> block;
    };
}
