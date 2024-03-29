#pragma once
#include <abyss/utils/NeptScript/Lexer/Token.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Nept
{
    class Lexer
    {
    public:
        Lexer(const s3d::FilePath& mns);
        Lexer(s3d::Arg::code_<s3d::String> code);

        bool load(const s3d::FilePath& ctfolder);
        bool load(s3d::Arg::code_<s3d::String> code);

        const s3d::Array<Token>& getTokens()const
        {
            return m_tokens;
        }
    public:
        void parseLine(const s3d::String& line);
    private:
        s3d::Array<Token> m_tokens;
    };
}
