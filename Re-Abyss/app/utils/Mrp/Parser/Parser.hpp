#pragma once
#include <memory>
#include <abyss/utils/Mrp/Lexer/Token.hpp>
#include <abyss/utils/Mrp/Mrp.hpp>
#include <Siv3D/Array.hpp>

namespace Mrp
{
    struct Error
    {
        s3d::String message;
    };
    class Parser
    {
        using Itr = s3d::Array<Token>::const_iterator;
        using Data = s3d::HashTable<s3d::String, MrpGroup>;
    public:
        Parser(const s3d::Array<Token>& tokens);

        std::unique_ptr<Data> group();
        const s3d::Array<Error> errors() const
        {
            return m_errors;
        }
    private:
        bool parseName(Itr& it, Data& ret);
        bool parseList(Itr& it, Data& ret);
        const s3d::Array<Token>& m_tokens;
        s3d::Array<Error> m_errors;
        s3d::String m_curtName;
    };
}