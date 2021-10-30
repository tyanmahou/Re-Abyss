#pragma once
#include <memory>
#include <abyss/utils/Mns/Lexer/Token.hpp>
#include <abyss/utils/Mns/Ast/Root.hpp>
#include <abyss/utils/Mns/Ast/IStatement.hpp>
#include <abyss/utils/Mns/Ast/Statement/TagStatement.hpp>
#include <abyss/utils/Mns/Ast/Statement/NameStatement.hpp>
#include <abyss/utils/Mns/Ast/Statement/TextStatement.hpp>
#include <Siv3D/Array.hpp>
namespace Mns
{
    struct Error
    {
        s3d::String message;
    };
    class Parser
    {
        using AstItr = s3d::Array<Token>::const_iterator;
    public:
        Parser(const s3d::Array<Token>& tokens);

        std::shared_ptr<Ast::Root> root();
    private:
        std::shared_ptr<Ast::Root> parseRoot(AstItr& it);
        std::shared_ptr<Ast::IStatement> parseStatement(AstItr& it);
        std::shared_ptr<Ast::TagStatement> parseTagStatement(AstItr& it);
        std::shared_ptr<Ast::NameStatement> parseNameStatement(AstItr& it);
        std::shared_ptr<Ast::TextStatement> parseTextStatement(AstItr& it);
    private:
        const s3d::Array<Token>& m_tokens;
        std::shared_ptr<Ast::Root> m_root = nullptr;
        s3d::Array<Error> m_errors;
    };
}