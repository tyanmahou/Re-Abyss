#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Mrp/Mrp.hpp>

namespace abyss::tests
{
    TEST_CASE("utils::Mrp::Mrp. Test")
    {
        SECTION("test normal")
        {
            Mrp::Mrp mrp(U"tests/data/mrp/test_01.mrp");
            REQUIRE(mrp);

            const auto& data = mrp.data();

            REQUIRE(data.contains(U"Test0"));
            {
                const auto& test0 = data.at(U"Test0");
                REQUIRE(test0.size() == 2);

                REQUIRE(test0[0].first == U"a");
                REQUIRE(test0[0].second == U"aaa");

                REQUIRE(test0[1].first == U"b");
                REQUIRE(test0[1].second == U"bbb");
            }

            REQUIRE(data.contains(U"Test1"));
            {
                const auto& test1 = data.at(U"Test1");
                REQUIRE(test1.size() == 2);

                REQUIRE(test1[0].first == U"c");
                REQUIRE(test1[0].second == U"ccc");

                REQUIRE(test1[1].first == U"d");
                REQUIRE(test1[1].second == U"ddd");
            }
        }
    }
}
#endif
