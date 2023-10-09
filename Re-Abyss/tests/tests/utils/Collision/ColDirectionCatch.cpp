#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

namespace abyss::tests
{
    TEST_CASE("utils ColDirection Test")
    {
        SECTION("basic") {
            ColDirection a = ColDirection::Left;
            REQUIRE_FALSE(a.isLeft());
            a = ColDirection::Right;
            REQUIRE_FALSE(a.isRight());
            a = ColDirection::Up;
            REQUIRE_FALSE(a.isUp());
            a = ColDirection::Down;
            REQUIRE_FALSE(a.isDown());
        }
        SECTION("operator bitwiaw or") {
            ColDirection a = ColDirection::Left | ColDirection::Right;
            REQUIRE_FALSE(a.isLeft());
            REQUIRE_FALSE(a.isRight());
            REQUIRE_FALSE(!a.isUp());
            REQUIRE_FALSE(!a.isDown());
        }
        SECTION("operator bitwiaw and") {
            ColDirection a = ColDirection::All & ColDirection::Right;
            REQUIRE_FALSE(!a.isLeft());
            REQUIRE_FALSE(a.isRight());
            REQUIRE_FALSE(!a.isUp());
            REQUIRE_FALSE(!a.isDown());
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
        }
    }
}
#endif ABYSS_DO_TEST
