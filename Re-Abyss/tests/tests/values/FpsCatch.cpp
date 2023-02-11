#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/values/Fps.hpp>

namespace abyss::tests
{
    TEST_CASE("values Fps Test")
    {
        constexpr Fps fps30 = 30_fps;
        constexpr Fps fps60 = 60_fps;
        constexpr Fps fps120 = 120_fps;

        SECTION("30 fps") {
            REQUIRE(fps30 == fps30);
            REQUIRE(fps30 < fps60);
            REQUIRE(fps30 < fps120);
            REQUIRE(fps30.duration().count() == 1 / 30.0);
            REQUIRE(fps30.frame(1.0) == 30.0);
        }

        SECTION("60 fps") {
            REQUIRE(fps60 > fps30);
            REQUIRE(fps60 == fps60);
            REQUIRE(fps60 < fps120);
            REQUIRE(fps60.duration().count() == 1 / 60.0);
            REQUIRE(fps60.frame(1.0) == 60.0);
        }

        SECTION("120 fps") {
            REQUIRE(fps120 > fps30);
            REQUIRE(fps120 > fps60);
            REQUIRE(fps120 == fps120);
            REQUIRE(fps120.duration().count() == 1 / 120.0);
            REQUIRE(fps120.frame(1.0) == 120.0);
        }
    }
}
#endif ABYSS_DO_TEST
