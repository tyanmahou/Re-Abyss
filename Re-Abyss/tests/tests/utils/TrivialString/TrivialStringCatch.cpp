#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/TrivialString/TrivialString.hpp>
#include <Siv3D.hpp>

namespace
{
}
namespace abyss::tests
{
    TEST_CASE("utils::TrivialString. Test")
    {
        SECTION("test normal")
        {
            TrivialString<8> str = U"AAA";
            REQUIRE(str.toString() == U"AAA");
        }
        SECTION("test length over")
        {
            TrivialString<8> str = U"123456789";
            REQUIRE(str.toString() == U"12345678");
        }
    }
}
#endif
