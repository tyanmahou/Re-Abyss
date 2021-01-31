#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/DateTime/DateTimeUtil.hpp>

namespace abyss::tests
{
    TEST_CASE("utils::DateTimeUtil. Test")
    {
        SECTION("test datetime")
        {
            s3d::DateTime dt = DateTimeUtil::ToDateTime(U"2020-01-08 12:01:02");
            REQUIRE(dt.year == 2020);
            REQUIRE(dt.month == 1);
            REQUIRE(dt.day == 8);
            REQUIRE(dt.hour == 12);
            REQUIRE(dt.minute == 1);
            REQUIRE(dt.second == 2);
        }

        SECTION("test date")
        {
            s3d::Date d = DateTimeUtil::ToDate(U"2020-01-08");
            REQUIRE(d.year == 2020);
            REQUIRE(d.month == 1);
            REQUIRE(d.day == 8);
        }

        SECTION("test duration")
        {
            auto d = DateTimeUtil::ToTimeDuration(U"12:01:02");
            REQUIRE(s3d::FormatTime(d, U"HH:mm:ss") == U"12:01:02");
        }

        SECTION("test datetime 2038")
        {
            s3d::DateTime dt = DateTimeUtil::ToDateTime(U"2040-01-08 12:01:02");
            REQUIRE(dt.year == 2040);
            REQUIRE(dt.month == 1);
            REQUIRE(dt.day == 8);
            REQUIRE(dt.hour == 12);
            REQUIRE(dt.minute == 1);
            REQUIRE(dt.second == 2);
        }
    }
}
#endif