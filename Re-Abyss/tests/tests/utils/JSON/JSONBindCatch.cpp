#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/JSON/JSONUtil.hpp>
#include <Siv3D.hpp>

namespace
{
    struct Test
    {
        [[JSON_BIND(num)]]
        int32 num;

        [[JSON_BIND(str, "string")]]
        String str;

        [[JSON_BIND(optNum)]]
        s3d::Optional<int32> optNum;

        [[JSON_BIND(ar)]]
        Array<int32> ar;
    };
    struct TestNestArray
    {
        [[JSON_BIND(nest)]]
        s3d::Array<Test> nest;
    };
    struct TestNestOpt
    {
        [[JSON_BIND(nest)]]
        s3d::Optional<Test> nest;
    };
}
namespace abyss::tests
{
    TEST_CASE("utils::JSONBind. Test")
    {
        SECTION("fromJSON")
        {
            JSON json;
            json[U"num"] = 334;
            json[U"string"] = U"Hello World";
            json[U"ar"] = {1, 2, 3};

            SECTION("test normal")
            {
                Test test = JSONUtil::FromJSON<Test>(json);
                REQUIRE(test.num == 334);
                REQUIRE(test.str == U"Hello World");
                REQUIRE_FALSE(test.optNum.has_value());
                REQUIRE(test.ar[0] == 1);
                REQUIRE(test.ar[1] == 2);
                REQUIRE(test.ar[2] == 3);
            }
            SECTION("test opt")
            {
                json[U"optNum"] = 114514;

                Test test = JSONUtil::FromJSON<Test>(json);
                REQUIRE(test.optNum == 114514);
            }

            SECTION("test nest ar")
            {
                JSON json2;
                json2[U"num"] = 335;
                json2[U"string"] = U"a";
                json2[U"ar"] = {1,2,3};

                JSON json3;
                json3[U"num"] = 336;
                json3[U"string"] = U"aa";
                json3[U"ar"] = { 1,2,3 };

                JSON jsonAr;
                jsonAr[U"nest"] = {
                    json,
                    json2,
                    json3,
                };

                auto test = JSONUtil::FromJSON<TestNestArray>(jsonAr);
                REQUIRE(test.nest.size() == 3);
                REQUIRE(test.nest[0].num == 334);
                REQUIRE(test.nest[0].str == U"Hello World");

                REQUIRE(test.nest[1].num == 335);
                REQUIRE(test.nest[1].str == U"a");

                REQUIRE(test.nest[2].num == 336);
                REQUIRE(test.nest[2].str == U"aa");
            }

            SECTION("test nest opt")
            {
                JSON jsonOpt;
                jsonOpt[U"nest"] = nullptr;

                auto test = JSONUtil::FromJSON<TestNestOpt>(jsonOpt);
                REQUIRE_FALSE(test.nest.has_value());

                jsonOpt[U"nest"] = json;
                test = JSONUtil::FromJSON<TestNestOpt>(jsonOpt);
                REQUIRE(test.nest->num == 334);
                REQUIRE(test.nest->str == U"Hello World");
                REQUIRE_FALSE(test.nest->optNum.has_value());
                REQUIRE(test.nest->ar[0] == 1);
                REQUIRE(test.nest->ar[1] == 2);
                REQUIRE(test.nest->ar[2] == 3);
            }
        }
        SECTION("toJSON")
        {
            Test test{
                .num = 334,
                .str = U"Hello World",
                .optNum = s3d::none,
                .ar = {1,2,3}
            };

            SECTION("test normal")
            {
                JSON json = JSONUtil::ToJSON(test);
                REQUIRE(json[U"num"].get<int32>() == 334);
                REQUIRE(json[U"string"].get<String>() == U"Hello World");
                REQUIRE(json[U"optNum"].isNull());
                REQUIRE(json[U"ar"][0].get<int32>() == 1);
                REQUIRE(json[U"ar"][1].get<int32>() == 2);
                REQUIRE(json[U"ar"][2].get<int32>() == 3);
            }
        }
    }
}
#endif
