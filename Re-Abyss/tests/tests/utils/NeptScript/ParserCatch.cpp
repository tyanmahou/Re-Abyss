#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/NeptScript/Script/Lexer/Lexer.hpp>
#include <abyss/utils/NeptScript/Script/Parser/Parser.hpp>

namespace abyss::tests
{
    TEST_CASE("utils::NeptScript::Parser. Test")
    {
        using namespace Nept;
        using enum Nept::TokenType;

        SECTION("test command")
        {
            s3d::String code = U"@wait time:1.0";
            Lexer lexer(s3d::Arg::code = code);
            Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Ast::CommandStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->command == U"wait");
            REQUIRE(!statement->rootParam);

            REQUIRE(statement->params.size() == 1);

            REQUIRE(statement->params[0].first == U"time");
            REQUIRE(statement->params[0].second == U"1.0");
        }

        SECTION("test inline command")
        {
            s3d::String code = U"[wait time:1.0]";
            Lexer lexer(s3d::Arg::code = code);
            Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Ast::CommandStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->command == U"wait");
            REQUIRE(!statement->rootParam);

            REQUIRE(statement->params.size() == 1);

            REQUIRE(statement->params[0].first == U"time");
            REQUIRE(statement->params[0].second == U"1.0");
        }

        SECTION("test chara")
        {
            s3d::String code = U"/Actor.emote/: Name";
            Lexer lexer(s3d::Arg::code = code);
            Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Ast::CharaStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->look == Nept::Ast::LookType::Left);
            REQUIRE(statement->actor == U"Actor");
            REQUIRE(statement->emote == U"emote");
            REQUIRE(statement->displayName == U"Name");
        }
        SECTION("test text")
        {
            s3d::String code = U""
                "AAA aaa\n"
                "BBB bbb\n"
                "\"CCC ccc\""
                ;
            Lexer lexer(s3d::Arg::code = code);
            Parser parser(lexer.getTokens());

            REQUIRE(!parser.root()->statements.empty());

            auto statement = std::dynamic_pointer_cast<Ast::TextStatement>(parser.root()->statements[0]);
            REQUIRE(statement != nullptr);

            REQUIRE(statement->text == U"AAAaaaBBBbbbCCC ccc");
        }
    }
}
#endif
