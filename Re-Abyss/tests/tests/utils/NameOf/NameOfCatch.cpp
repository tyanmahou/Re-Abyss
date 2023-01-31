#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/NameOf/NameOf.hpp>
#include <Siv3D.hpp>

namespace
{
    namespace Test
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
}

namespace abyss::tests
{
    TEST_CASE("utils::NameOf. Test")
    {
        SECTION("test normal")
        {
            REQUIRE(NameOf::nameof<Test::TestEnum>() == U"TestEnum");
            REQUIRE(NameOf::nameof<Test::TestEnumClass>() == U"TestEnumClass");
            REQUIRE(NameOf::nameof<Test::TestStruct>() == U"TestStruct");
            REQUIRE(NameOf::nameof<Test::TestClass>() == U"TestClass");

            REQUIRE(NameOf::nameof<Test::TestEnum::A>() == U"A");
            REQUIRE(NameOf::nameof<Test::TestEnumClass::A>() == U"A");
        }

        SECTION("test full")
        {
            const String anonymousNamespacePrefix = U"`anonymous-namespace'::";

            REQUIRE(NameOf::nameof_full<Test::TestEnum>() == anonymousNamespacePrefix + U"Test::TestEnum");
            REQUIRE(NameOf::nameof_full<Test::TestEnumClass>() == anonymousNamespacePrefix + U"Test::TestEnumClass");
            //REQUIRE(NameOf::nameof_full<Test::TestStruct>() == anonymousNamespacePrefix + U"Test::TestStruct");
            //REQUIRE(NameOf::nameof_full<Test::TestClass>() == U"TestClass");

            REQUIRE(NameOf::nameof_full<Test::TestEnum::A>() == anonymousNamespacePrefix + U"Test::A");
            REQUIRE(NameOf::nameof_full<Test::TestEnumClass::A>() == anonymousNamespacePrefix + U"Test::TestEnumClass::A");
        }
    }
}

#endif
