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

        SECTION("test tag")
        {
            s3d::String code = U"[wait time=1.0]";
            Mns::Lexer lexer(s3d::Arg::code = code);
            Mns::Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::TagStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->tag.first == U"wait");
            REQUIRE(!statement->tag.second);

            REQUIRE(statement->childs.size() == 1);

            REQUIRE(statement->childs[0].first == U"time");
            REQUIRE(statement->childs[0].second == U"1.0");
        }

        SECTION("test name")
        {
            s3d::String code = U"# Name";
            Mns::Lexer lexer(s3d::Arg::code = code);
            Mns::Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::NameStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->name == U"Name");
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

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::TextStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->text == U"AAAaaaBBBbbbCCC ccc");
        }
        SECTION("test text invalid new line for file")
        {
            Mns::Lexer lexer(U"tests/data/novels/novel_test_02.mns");
            Mns::Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Mns::Ast::TextStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->text == U"AAA aaa \\n BBB bbb");
        }
    }
}
#endif