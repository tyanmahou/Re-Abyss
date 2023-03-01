#include <abyss/utils/NeptScript/Script/Parser/Parser.hpp>

namespace abyss::Nept
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
        while (it != m_tokens.end()) {
            if (auto statement = this->parseStatement(it)) {
                root->statements << statement;
            } else {
                break;
            }
        }
        return root;
    }
    std::shared_ptr<IStatement> Parser::parseStatement(AstItr& it)
    {
        if (it->type == TokenType::At) {
            auto nextIt = it + 1;
            if (nextIt != m_tokens.end() && nextIt->value == U"section") {
                return this->parseSectionStatement(it);
            }
            return this->parseCommandStatement(it);
        } else if (it->type == TokenType::Slash || it->type == TokenType::BackSlash || it->type == TokenType::Pipe) {
            return this->parseCharaStatement(it);
        } else if (it->type == TokenType::Text) {
            return this->parseTextStatement(it);
        } else if (it->type == TokenType::LBracket) {
            return this->parseInlineCommandStatement(it);
        } else if (it->type == TokenType::LBrace) {
            return this->parseBlockStatement(it);
        }
        return nullptr;
    }
    std::shared_ptr<CommandStatement> Parser::parseCommandStatement(AstItr& it)
    {
        // @
        ++it;

        return this->parseCommandStatementImpl(it);
    }
    std::shared_ptr<CommandStatement> Parser::parseInlineCommandStatement(AstItr& it)
    {
        // [
        ++it;

        auto statement = this->parseCommandStatementImpl(it);

        // ]
        if (it == m_tokens.end() || it->type != TokenType::RBracket) {
            m_errors.emplace_back(U"Not Found Inline Command Param ]");
            return nullptr;
        }
        ++it;
        return statement;
    }
    std::shared_ptr<CommandStatement> Parser::parseCommandStatementImpl(AstItr& it)
    {
        auto statement = std::make_shared<CommandStatement>();

        bool isFirst = true;
        while (it != m_tokens.end()) {
            CommandParam param;

            // Key設定
            if (isFirst && it->type == TokenType::Slash) {
                param.first += U"/";

                ++it;
            }
            if (it == m_tokens.end() || it->type != TokenType::Ident) {
                m_errors.emplace_back(U"Command Param is required ident key");
                return nullptr;
            }
            param.first += it->value;

            ++it;
            if (it != m_tokens.end() && it->type == TokenType::Colon) {
                // Value設定 (opt)

                // :
                ++it;

                if (it == m_tokens.end() || it->type != TokenType::Value) {
                    m_errors.emplace_back(U"Not Found Command Param Value");
                    return nullptr;
                }

                param.second = it->value;

                // value
                ++it;
            }

            if (isFirst) {
                statement->command = std::move(param.first);
                statement->rootParam = std::move(param.second);
            } else {
                statement->params << std::move(param);
            }
            isFirst = false;

            if (it == m_tokens.end() || it->type != TokenType::Ident) {
                break;
            }
        }
        return statement;
    }
    std::shared_ptr<CharaStatement> Parser::parseCharaStatement(AstItr& it)
    {
        // Look
        LookType look = LookType::Left;
        String lookValue;
        if (it->type == TokenType::Slash) {
            look = LookType::Left;
        } else if (it->type == TokenType::BackSlash) {
            look = LookType::Right;
        } else if (it->type == TokenType::Pipe) {
            look = LookType::Center;
        }
        lookValue = it->value;
        ++it;

        // Actor
        if (it == m_tokens.end() || it->type != TokenType::Value) {
            m_errors.emplace_back(U"Not Found Actor Name");
            return nullptr;
        }
        String actor = it->value;
        s3d::Optional<String> emote;
        ++it;
        // Emote
        if (it != m_tokens.end() && it->type == TokenType::Dot) {
            ++it; // .
            emote = it->value;
            ++it;
        }
        if (it == m_tokens.end() || it->value != lookValue) {
            m_errors.emplace_back(U"Not Match Token / or \\ or | ");
            return nullptr;
        }
        ++it;

        s3d::Optional<String> displayName;
        if (it != m_tokens.end() && it->type == TokenType::Colon) {
            ++it; // :
            if (it == m_tokens.end() || it->type != TokenType::Value) {
                m_errors.emplace_back(U"Not Found Display Name");
                return nullptr;
            }
            displayName = it->value;
            ++it;
        }
        auto statement = std::make_shared<CharaStatement>();
        statement->look = look;
        statement->actor = std::move(actor);
        statement->emote = std::move(emote);
        statement->displayName = std::move(displayName);
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
        ++it;
        return statement;
    }

    std::shared_ptr<BlockStatement> Parser::parseBlockStatement(AstItr& it)
    {
        ++it; // {
        auto block = std::make_shared<BlockStatement>();
        while (it != m_tokens.end()) {
            if (auto statement = this->parseStatement(it)) {
                block->statements << statement;
            } else {
                break;
            }
        }
        // }
        if (it == m_tokens.end() || it->type != TokenType::RBrace) {
            m_errors.emplace_back(U"Not Found }");
            return nullptr;
        }
        ++it;

        return block;
    }
    std::shared_ptr<SectionStatement> Parser::parseSectionStatement(AstItr& it)
    {
        ++it; // @
        ++it; // section
        if (it == m_tokens.end() || it->type != TokenType::Colon) {
            m_errors.emplace_back(U"Not Found Section Colon");
            return nullptr;
        }
        ++it; // :

        if (it == m_tokens.end() || it->type != TokenType::Value) {
            m_errors.emplace_back(U"Not Found Section Name");
            return nullptr;
        }
        String section = it->value;
        ++it;
        if (it == m_tokens.end() || it->type != TokenType::LBrace) {
            m_errors.emplace_back(U"Not Found Section Block");
            return nullptr;
        }
        std::shared_ptr<BlockStatement> block = this->parseBlockStatement(it);
        if (!block) {
            return nullptr;
        }
        auto statement = std::make_shared<SectionStatement>();
        statement->section = std::move(section);
        statement->block = block;
        return statement;
    }
}
