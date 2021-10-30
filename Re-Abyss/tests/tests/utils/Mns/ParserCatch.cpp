#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Mns/Lexer/Lexer.hpp>
#include <abyss/utils/Mns/Parser/Parser.hpp>

namespace
{
}
namespace abyss::tests
{
    TEST_CASE("utils::Msn::Parser. Test")
    {
        using enum Mns::TokenType;
        SECTION("test name")
        {
            s3d::String code = U"# Name";
            Mns::Lexer lexer(s3d::Arg::code = code);
            Mns::Parser parser(lexer.getTokens());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::NameStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            if (statement) {
                REQUIRE(statement->name == U"Name");
            }
        }
        SECTION("test text")
        {
            s3d::String code = U""
                "AAA aaa\n"
                "BBB bbb\n"
                "\"CCC ccc\""
                ;
            Mns::Lexer lexer(s3d::Arg::code = code);
            Mns::Parser parser(lexer.getTokens());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::TextStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            if (statement) {
                REQUIRE(statement->text == U"AAAaaaBBBbbbCCC ccc");
            }
        }
    }
}
#endif