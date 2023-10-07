#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/BiMap/HashBiMap.hpp>

namespace abyss::tests
{
    TEST_CASE("utils BidirectionalHashMap Test")
    {
        SECTION("Normal") {
            HashBiMap<int, String> map;
            map.emplace(0, U"aaa");

            REQUIRE(map.value(0) == U"aaa");
            REQUIRE(map.key(U"aaa") == 0);

            // exception
            REQUIRE_THROWS(map.value(100));
            REQUIRE_THROWS(map.key(U"bbb"));

            // const
            const HashBiMap<int, String>& cmap = map;
            REQUIRE(cmap.value(0) == U"aaa");
            REQUIRE(cmap.key(U"aaa") == 0);
        }

        SECTION("Same Type") {
            HashBiMap<int, int> map;
            map.emplace(10, 20);
            REQUIRE(map.value(10) == 20);
            REQUIRE(map.key(20) == 10);

            // exception
            REQUIRE_THROWS(map.value(20));
            REQUIRE_THROWS(map.key(10));

            // const
            const HashBiMap<int, int>& cmap = map;
            REQUIRE(cmap.value(10) == 20);
            REQUIRE(cmap.key(20) == 10);
        }
    }
}
#endif ABYSS_DO_TEST
