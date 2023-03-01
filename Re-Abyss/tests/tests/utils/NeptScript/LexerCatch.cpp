#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/NeptScript/Lexer/Lexer.hpp>

namespace
{
}
namespace abyss::tests
{
    TEST_CASE("utils::NeptScript::Lexer. Test")
    {
        using namespace Nept;
        using enum Nept::TokenType;

        SECTION("test normal")
        {
            s3d::String code = UR"(
            @command:"value0" key1:value1 key2:"value2"
            /Actor/: Name
            Hello, NeptScript
            )";
            Lexer lexer(s3d::Arg::code = code);
            const auto& tokens = lexer.getTokens();
            s3d::Array<Token> anser{
                {At, U"@"}, {Ident, U"command"}, {Colon, U":"}, {Value, U"value0"}, {Ident, U"key1"}, {Colon, U":"},{Value, U"value1"}, {Ident, U"key2"}, {Colon, U":"}, {Value, U"value2"},
                {Slash, U"/"}, {Value, U"Actor"},{Slash, U"/"},{Colon, U":"},{Value, U"Name"},
                {Text, U"Hello, NeptScript"},
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
            Lexer lexer(s3d::Arg::code = code);
            REQUIRE(lexer.getTokens().isEmpty());
        }

        SECTION("test white space text")
        {
            Lexer lexer(s3d::Arg::code = U"   　　text");
            const auto& tokens = lexer.getTokens();
            s3d::Array<Token> anser{
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
