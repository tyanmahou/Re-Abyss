#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Mns/Lexer/Lexer.hpp>

namespace
{
}
namespace abyss::tests
{
    TEST_CASE("utils::Msn::Lexer. Test")
    {
        using enum Mns::TokenType;
        SECTION("test normal")
        {
            Mns::Lexer lexer(U"tests/data/novels/novel_test_01.mns");
            const auto& tokens = lexer.getTokens();
            s3d::Array<Mns::Token> anser{
                {Sharp, U"#"},{Text, U"なまえ"},
                {LSqBrace, U"["},{Ident, U"shake"},{RSqBrace, U"]"},
                {Text, U"ゆれる文字"},
                {LSqBrace, U"["},{Slash, U"/"}, {Ident, U"shake"},{RSqBrace, U"]"},

                {LSqBrace, U"["},{Ident, U"wait"},{Ident, U"time"},{Assign, U"="},{Value, U"1.0"},{RSqBrace, U"]"},

                {LSqBrace, U"["},{Ident, U"color"},{Assign, U"="},{Value, U"#FF0000"},{RSqBrace, U"]"},
                {Text, U"赤色"},
                {LSqBrace, U"["},{Slash, U"/"},{Ident, U"color"},{RSqBrace, U"]"},
            };

            for (size_t i = 0; i < anser.size(); ++i) {
                REQUIRE(tokens[i].value == anser[i].value);
                REQUIRE(tokens[i].type == anser[i].type);
            }
        }

        SECTION("test comment")
        {
            s3d::String code = U""
                ";コメント\n"
                "; コメント\n";
            Mns::Lexer lexer(s3d::Arg::code = code);
            REQUIRE(lexer.getTokens().isEmpty());
        }

        SECTION("test white space text")
        {
            Mns::Lexer lexer(s3d::Arg::code = U"   　　text");
            const auto& tokens = lexer.getTokens();
            s3d::Array<Mns::Token> anser{
                {Text, U"text"},
            };

            for (size_t i = 0; i < anser.size(); ++i) {
                REQUIRE(tokens[i].value == anser[i].value);
                REQUIRE(tokens[i].type == anser[i].type);
            }
        }
    }
}
#endif
