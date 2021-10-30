#include "Parser.hpp"

namespace Mns
{
    using namespace Ast;

    Parser::Parser(const s3d::Array<Token>& tokens) :
        m_tokens(tokens)
    {}
    std::shared_ptr<Root> Parser::root()
    {
        if (m_root) {
            return m_root;
        }
        auto it = m_tokens.begin();
        return m_root = parseRoot(it);
    }

    std::shared_ptr<Root> Parser::parseRoot(AstItr& it)
    {
        auto root = std::make_shared<Root>();
        while(it != m_tokens.end()) {
            if (auto statement = this->parseStatement(it)) {
                root->statements << statement;
            } else {
                break;
            }
            ++it;
        }
        return root;
    }
    std::shared_ptr<IStatement> Parser::parseStatement(AstItr& it)
    {
        if (it->type == TokenType::LSqBrace) {
            return this->parseTagStatement(it);
        } else if (it->type == TokenType::Sharp) {
            return this->parseNameStatement(it);
        } else if (it->type == TokenType::Text) {
            return this->parseTextStatement(it);
        }
        return nullptr;
    }
    std::shared_ptr<TagStatement> Parser::parseTagStatement(AstItr& it)
    {
        return nullptr;
    }
    std::shared_ptr<NameStatement> Parser::parseNameStatement(AstItr& it)
    {
        // #記号
        ++it;

        if (it->type != TokenType::Text) {
            m_errors.emplace_back(U"Not Found Name");
            return nullptr;
        }
        auto statement = std::make_shared<NameStatement>();
        statement->name = it->value;
        return statement;
    }
    std::shared_ptr<TextStatement> Parser::parseTextStatement(AstItr& it)
    {
        auto statement = std::make_shared<TextStatement>();
        while (true) {
            statement->text += it->value;

            auto nextIt = it + 1;
            if (nextIt != m_tokens.end() && nextIt->type == TokenType::Text) {
                // 次も文章なら結合
                ++it;
            } else {
                break;
            }
        }
        return statement;
    }
}
