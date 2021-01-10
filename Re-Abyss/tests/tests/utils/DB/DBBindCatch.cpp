#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/DB/DBBind.hpp>
#include <Siv3D.hpp>
namespace
{
    struct TestData
    {
        [[DB_COLUMN(intValue, "intValue")]]
        int32 intValue;

        [[DB_COLUMN(str)]]
        String str;

        [[DB_COLUMN_OPT(intOptFound)]]
        int32 intOptFound;
        [[DB_COLUMN_OPT(intOptFoundDefault, "intOptFoundDefault", 336)]]
        int32 intOptFoundDefault;
        [[DB_COLUMN_OPT(intOptNotFound, "intOptNotFound")]]
        int32 intOptNotFound;
        [[DB_COLUMN_OPT(intOptNotFoundDefault, "intOptNotFoundDefault", 338)]]
        int32 intOptNotFoundDefault;
    };
}
namespace abyss::tests
{
    TEST_CASE("utils::DBBind. Test")
    {
        s3dsql::DBRow row;
        row[U"intValue"] = 334;
        row[U"str"] = U"test";

        row[U"intOptFound"] = 335;
        row[U"intOptFoundDefault"] = 1;
        // intOptNotFound
        // intOptNotFoundDefault

        SECTION("test column")
        {
            auto data = FromRow<TestData>(row);
            REQUIRE(data.intValue == 334);
            REQUIRE(data.str == U"test");
        }
        SECTION("test column opt")
        {
            auto data = FromRow<TestData>(row);
            REQUIRE(data.intOptFound == 335);
            REQUIRE(data.intOptFoundDefault == 1);
            REQUIRE(data.intOptNotFound == 0);
            REQUIRE(data.intOptNotFoundDefault == 338);
        }
    }
}
#endif