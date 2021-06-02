#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/models/Temporary/TempFlag/TempFlagsModel.hpp>
namespace abyss::tests
{
    TEST_CASE("Temporary::TempFlag. Sample Test")
    {
        auto key1 = TempKey::ItemGet(1);
        auto key2 = TempKey::ItemGet(2);
        auto key3 = TempKey::ItemGet(3);

        SECTION("test add")
        {
            TempFlagsModel flags;
            flags.add(key1, TempLevel::Room);
            REQUIRE(flags.isContain(key1));
            REQUIRE(!flags.isContain(key2));
        }
        SECTION("test clear success")
        {
            TempFlagsModel flags;
            flags.add(key1, TempLevel::Room);
            flags.clear(TempLevel::Room);
            REQUIRE(!flags.isContain(key1));
        }
        SECTION("test clear failuer")
        {
            TempFlagsModel flags;
            flags.add(key1, TempLevel::Restart);
            flags.clear(TempLevel::Room);
            REQUIRE(flags.isContain(key1));
        }
        SECTION("test clear complex")
        {
            TempFlagsModel flags;
            flags.add(key1, TempLevel::Room);
            flags.add(key2, TempLevel::Restart);
            flags.add(key3, TempLevel::Exit);
            flags.clear(TempLevel::Restart);
            REQUIRE(!flags.isContain(key1));
            REQUIRE(!flags.isContain(key2));
            REQUIRE(flags.isContain(key3));
        }

        SECTION("test dupulicated")
        {
            TempFlagsModel flags;
            REQUIRE(flags.add(key1, TempLevel::Exit));
            REQUIRE(!flags.add(key1, TempLevel::Room));

            REQUIRE(flags.add(key2, TempLevel::Room));
            REQUIRE(flags.add(key2, TempLevel::Exit));
            flags.clear(TempLevel::Restart);
            REQUIRE(flags.isContain(key1));
            REQUIRE(flags.isContain(key2));
        }
    }
}
#endif ABYSS_DO_TEST