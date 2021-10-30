#pragma once
#include <abyss/utils/Mns/Ast/IStatement.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace Mns::Ast
{
    using TagKeyValue = std::pair<s3d::String, s3d::Optional<s3d::String>>;

    struct TagStatement : IStatement
    {
        TagKeyValue tag;
        s3d::Array<TagKeyValue> childs;
    };
}