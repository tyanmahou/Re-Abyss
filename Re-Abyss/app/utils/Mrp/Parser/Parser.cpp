#include "Parser.hpp"

namespace Mrp
{
    Parser::Parser(const s3d::Array<Token>& tokens) :
        m_tokens(tokens)
    {}
    std::unique_ptr<Parser::Data> Parser::group()
    {
        auto ret = std::make_unique<Parser::Data>();

        auto it = m_tokens.begin();
        while (it != m_tokens.end()) {
            if (it->type == TokenType::LSqBrace) {
                if (!this->parseName(it, *ret)) {
                    return nullptr;
                }
            } else if (it->type == TokenType::Bar) {
                if (!this->parseList(it, *ret)) {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
            ++it;
        }

        return ret;
    }
    bool Parser::parseName(Itr& it, Data& ret)
    {
        // [
        ++it;

        if (it == m_tokens.end() || it->type != TokenType::Value) {
            m_errors.emplace_back(U"Not Found Name");
            return false;
        }
        m_curtName = it->value;
        ret.emplace(m_curtName);

        ++it;
        if (it == m_tokens.end() || it->type != TokenType::RSqBrace) {
            m_errors.emplace_back(U"Not Found ]");
            return false;
        }
        return true;
    }
    bool Parser::parseList(Itr & it, Data& ret)
    {
        if (m_curtName.isEmpty()) {
            m_errors.emplace_back(U"Not Found Name");
            return false;
        }
        // -
        ++it;

        if (it == m_tokens.end() || it->type != TokenType::Ident) {
            m_errors.emplace_back(U"Not Found Ident");
            return false;
        }
        const auto& key = it->value;
        ++it;
        if (it == m_tokens.end() || it->type != TokenType::Value) {
            m_errors.emplace_back(U"Not Found Path");
            return false;
        }
        const auto& value = it->value;

        ret[m_curtName].emplace_back(key, value);
        return true;
    }
}
