#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/NameOf/NameOf.hpp>
#include <Siv3D.hpp>

namespace
{
    enum TestEnum
    {
        A, B, C
    };
    enum class TestEnumClass
    {
        A, B, C
    };
    struct TestStruct
    {};
    struct TestClass
    {};
}

namespace abyss::tests
{
    TEST_CASE("utils::NameOf. Test")
    {
        SECTION("test normal")
        {
            REQUIRE(NameOf::nameof<TestEnum>() == U"TestEnum");
            REQUIRE(NameOf::nameof<TestEnumClass>() == U"TestEnumClass");
            REQUIRE(NameOf::nameof<TestStruct>() == U"TestStruct");
            REQUIRE(NameOf::nameof<TestClass>() == U"TestClass");

            REQUIRE(NameOf::nameof<TestEnum::A>() == U"A");
            REQUIRE(NameOf::nameof<TestEnumClass::A>() == U"A");
        }
    }
}

#endif
