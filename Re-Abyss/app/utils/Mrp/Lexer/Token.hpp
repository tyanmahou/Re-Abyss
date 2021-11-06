#pragma once
#include <Siv3D/String.hpp>

namespace Mrp
{
    /// <summary>
    /// トークンタイプ
    /// </summary>
    enum class TokenType
    {
        /// <summary>無効値</summary>
        Invalid,

        /// <summary>-</summary>
        Bar,

        /// <summary>括弧 [</summary>
        LSqBrace,
        /// <summary>括弧 ]</summary>
        RSqBrace,

        /// <summary>識別子</summary>
        Ident,

        /// <summary>値</summary>
        Value,
    };

    /// <summary>
    /// トークン
    /// </summary>
    struct Token
    {
        Token() = default;

        Token(TokenType _type, const s3d::String& _value):
            type(_type),
            value(_value)
        {}
        Token(TokenType _type, s3d::String&& _value) noexcept:
            type(_type),
            value(std::move(_value))
        {}
        TokenType type;
        s3d::String value;
    };
}