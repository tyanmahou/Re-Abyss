#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

namespace abyss::tests
{
    TEST_CASE("utils ColDirection Test")
    {
        SECTION("basic") {
            ColDirection a = ColDirection::Left;
            REQUIRE(a.isLeft());
            a = ColDirection::Right;
            REQUIRE(a.isRight());
            a = ColDirection::Up;
            REQUIRE(a.isUp());
            a = ColDirection::Down;
            REQUIRE(a.isDown());
        }
        SECTION("operator bitwise or") {
            ColDirection a = ColDirection::Left | ColDirection::Right;
            REQUIRE(a.isLeft());
            REQUIRE(a.isRight());
            REQUIRE(!a.isUp());
            REQUIRE(!a.isDown());
        }
        SECTION("operator bitwise and") {
            ColDirection a = ColDirection::All & ColDirection::Right;
            REQUIRE(!a.isLeft());
            REQUIRE(a.isRight());
            REQUIRE(!a.isUp());
            REQUIRE(!a.isDown());
        }
        SECTION("Ignore All") {
            ColDirection ignore = ColDirection::All;
            ColDirection a = ColDirection::Left | ColDirection::Up;
            a.ignore(ignore);
            REQUIRE(a.isNone());

            ColDirection b = ColDirection::Left | ColDirection::Down;
            b.ignore(ignore);
            REQUIRE(b.isNone());

            REQUIRE(a == b);
            REQUIRE_FALSE(a != b);
        }
        SECTION("Ignored") {
            const ColDirection a = ColDirection::Left | ColDirection::Up;
            const ColDirection ai = a.ignored(ColDirection::Up);
            REQUIRE(ai.isLeft());

            const ColDirection b = ColDirection::Left | ColDirection::Down;
            const ColDirection bi = b.ignored(ColDirection::Down);

            REQUIRE(bi.isLeft());

            REQUIRE(ai == bi);
            REQUIRE_FALSE(ai != bi);
        }
        SECTION("Ignore ForVelocity") {
            ColDirection a = ColDirection::Left | ColDirection::Up;
            a.ignoreForVelocity(Vec2::Up());
            REQUIRE(a.isLeft());

            a.ignoreForVelocity(Vec2:: Left());
            REQUIRE(a.isNone());
        }
    }
}
#endif ABYSS_DO_TEST
