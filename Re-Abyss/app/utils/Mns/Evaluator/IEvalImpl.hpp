#pragma once
#include <abyss/utils/Mns/Ast/Statement/NameStatement.hpp>
#include <abyss/utils/Mns/Ast/Statement/TagStatement.hpp>
#include <abyss/utils/Mns/Ast/Statement/TextStatement.hpp>

namespace Mns
{
    class IEvalImpl
    {
    public:
        virtual ~IEvalImpl() = default;

        virtual void eval(const Ast::TagStatement& statement) = 0;
        virtual void eval(const Ast::NameStatement& statement) = 0;
        virtual void eval(const Ast::TextStatement& statement) = 0;
    };
}
