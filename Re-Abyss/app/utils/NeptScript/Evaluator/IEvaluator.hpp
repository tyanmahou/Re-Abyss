#pragma once
#include <abyss/utils/NeptScript/Ast/Statement/CharaStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/CommandStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/TextStatement.hpp>
#include <abyss/utils/NeptScript/Parser/Error.hpp>

namespace abyss::Nept
{
    class IEvaluator
    {
    public:
        virtual ~IEvaluator() = default;

        virtual void eval(const Ast::CharaStatement& statement) = 0;
        virtual void eval(const Ast::CommandStatement& statement) = 0;
        virtual void eval(const Ast::TextStatement& statement) = 0;

        virtual void evalOnSectionStart(const s3d::String& section) = 0;
        virtual void evalOnSectionEnd(const s3d::String& section) = 0;


        virtual void error(const s3d::Array<Error>& errors) = 0;
    };
}
