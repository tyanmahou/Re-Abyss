#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/values/Forward.hpp>

namespace abyss::tests
{
    TEST_CASE("values Forward Test")
    {
        SECTION("None") {
            auto forward = Forward::None();
            REQUIRE(forward == Forward::None());

            REQUIRE_FALSE(forward.isLeft());
            REQUIRE_FALSE(forward.isRight());
            REQUIRE_FALSE(forward.isUp());
            REQUIRE_FALSE(forward.isDown());

            REQUIRE(forward.signH() == 0);
            REQUIRE(forward.signV() == 0);

            REQUIRE(forward.toVec2() == Vec2{0, 0});
        }
        SECTION("Left") {
            auto forward = Forward::Left();
            REQUIRE(forward == Forward::Left());

            REQUIRE(forward.isLeft());
            REQUIRE_FALSE(forward.isRight());
            REQUIRE_FALSE(forward.isDown());
            REQUIRE_FALSE(forward.isUp());

            REQUIRE(forward.signH() < 0);
            REQUIRE(forward.signV() == 0);

            REQUIRE(forward.toVec2() == Vec2{ -1, 0 });
        }
        SECTION("Right") {
            auto forward = Forward::Right();
            REQUIRE(forward == Forward::Right());

            REQUIRE_FALSE(forward.isLeft());
            REQUIRE(forward.isRight());
            REQUIRE_FALSE(forward.isDown());
            REQUIRE_FALSE(forward.isUp());

            REQUIRE(forward.signH() > 0);
            REQUIRE(forward.signV() == 0);

            REQUIRE(forward.toVec2() == Vec2{ 1, 0 });
        }
        SECTION("Up") {
            auto forward = Forward::Up();
            REQUIRE(forward == Forward::Up());

            REQUIRE_FALSE(forward.isLeft());
            REQUIRE_FALSE(forward.isRight());
            REQUIRE_FALSE(forward.isDown());
            REQUIRE(forward.isUp());

            REQUIRE(forward.signH() == 0);
            REQUIRE(forward.signV() < 0);

            REQUIRE(forward.toVec2() == Vec2{ 0, -1 });
        }
        SECTION("Down") {
            auto forward = Forward::Down();
            REQUIRE(forward == Forward::Down());

            REQUIRE_FALSE(forward.isLeft());
            REQUIRE_FALSE(forward.isRight());
            REQUIRE(forward.isDown());
            REQUIRE_FALSE(forward.isUp());

            REQUIRE(forward.signH() == 0);
            REQUIRE(forward.signV() > 0);

            REQUIRE(forward.toVec2() == Vec2{ 0, 1 });
        }
    }
}
#endif ABYSS_DO_TEST
