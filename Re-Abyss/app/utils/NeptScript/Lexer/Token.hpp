#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Nept
{
    enum class TokenType
    {
        /// <summary>無効値</summary>
        Invalid,

        /// <summary>/</summary>
        Slash,
        /// <summary>\</summary>
        BackSlash,
        /// <summary>|</summary>
        Pipe,

        /// <summary>#</summary>
        Sharp,

        /// <summary>@</summary>
        At,

        /// <summary>括弧 [</summary>
        LBracket,
        /// <summary>括弧 ]</summary>
        RBracket,

        /// <summary>括弧 {</summary>
        LBrace,
        /// <summary>括弧 }</summary>
        RBrace,

        /// <summary>識別子</summary>
        Ident,

        /// <summary>値</summary>
        Value,

        /// <summary>=</summary>
        Colon,

        /// <summary>.</summary>
        Dot,

        /// <summary>テキスト</summary>
        Text
    };

    /// <summary>
    /// トークン
    /// </summary>
    struct Token
    {
        Token() = default;

        Token(TokenType _type, const s3d::String& _value) :
            type(_type),
            value(_value)
        {}
        Token(TokenType _type, s3d::String&& _value) noexcept :
            type(_type),
            value(std::move(_value))
        {}
        TokenType type;
        s3d::String value;
    };
}
