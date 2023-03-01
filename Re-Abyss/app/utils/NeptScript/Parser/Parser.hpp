#include <memory>
#include <abyss/utils/NeptScript/Lexer/Token.hpp>
#include <abyss/utils/NeptScript/Ast/Root.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/SectionStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/CommandStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/CharaStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/TextStatement.hpp>
#include <abyss/utils/NeptScript/Parser/Error.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Nept
{
    class Parser
    {
        using AstItr = s3d::Array<Token>::const_iterator;
    public:
        Parser(const s3d::Array<Token>& tokens);

        std::shared_ptr<Ast::Root> root();
        const s3d::Array<Error>& errors() const
        {
            return m_errors;
        }
    private:
        std::shared_ptr<Ast::Root> parseRoot(AstItr& it);
        std::shared_ptr<Ast::IStatement> parseStatement(AstItr& it);
        std::shared_ptr<Ast::CommandStatement> parseCommandStatement(AstItr& it);
        std::shared_ptr<Ast::CommandStatement> parseInlineCommandStatement(AstItr& it);
        std::shared_ptr<Ast::CommandStatement> parseCommandStatementImpl(AstItr& it);
        std::shared_ptr<Ast::CharaStatement> parseCharaStatement(AstItr& it);
        std::shared_ptr<Ast::TextStatement> parseTextStatement(AstItr& it);
        std::shared_ptr<Ast::BlockStatement> parseBlockStatement(AstItr& it);
        std::shared_ptr<Ast::SectionStatement> parseSectionStatement(AstItr& it);
    private:
        const s3d::Array<Token>& m_tokens;
        std::shared_ptr<Ast::Root> m_root = nullptr;
        s3d::Array<Error> m_errors;
    };
}

