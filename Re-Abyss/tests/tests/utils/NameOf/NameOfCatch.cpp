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

        template<class T>
        struct TestTemplate
        {};

        template<auto T>
        struct TestTemplateValue
        {};
    }
}

namespace abyss::tests
{
    TEST_CASE("utils::NameOf. Test")
    {
        const String anonymousNamespacePrefix = U"`anonymous-namespace'::";

        SECTION("test literal")
        {
           REQUIRE(NameOf::nameof<int>() == U"int");
           REQUIRE(NameOf::nameof_full<int>() == U"int");

           REQUIRE(NameOf::nameof<int*>() == U"int*");
           REQUIRE(NameOf::nameof_full<int*>() == U"int*");
        }
        SECTION("test enum")
        {
            REQUIRE(NameOf::nameof<Test::TestEnum>() == U"TestEnum");
            REQUIRE(NameOf::nameof_full<Test::TestEnum>() == anonymousNamespacePrefix + U"Test::TestEnum");
        }
        SECTION("test enum class")
        {
            REQUIRE(NameOf::nameof<Test::TestEnumClass>() == U"TestEnumClass");
            REQUIRE(NameOf::nameof_full<Test::TestEnumClass>() == anonymousNamespacePrefix + U"Test::TestEnumClass");
        }
        SECTION("test struct")
        {
            REQUIRE(NameOf::nameof<Test::TestStruct>() == U"TestStruct");
            REQUIRE(NameOf::nameof_full<Test::TestStruct>() == anonymousNamespacePrefix + U"Test::TestStruct");
        }
        SECTION("test class")
        {
            REQUIRE(NameOf::nameof<Test::TestClass>() == U"TestClass");
            REQUIRE(NameOf::nameof_full<Test::TestClass>() == anonymousNamespacePrefix + U"Test::TestClass");
        }
        SECTION("test enum value")
        {
            REQUIRE(NameOf::nameof<Test::TestEnum::A>() == U"A");
            REQUIRE(NameOf::nameof_full<Test::TestEnum::A>() == anonymousNamespacePrefix + U"Test::A");
        }
        SECTION("test enum class value")
        {
            REQUIRE(NameOf::nameof<Test::TestEnumClass::A>() == U"A");
            REQUIRE(NameOf::nameof_full<Test::TestEnumClass::A>() == anonymousNamespacePrefix + U"Test::TestEnumClass::A");
        }

        SECTION("test template")
        {
            REQUIRE(NameOf::nameof<Test::TestTemplate<int>>() == U"TestTemplate<int>");
            REQUIRE(NameOf::nameof_full<Test::TestTemplate<int>>() == anonymousNamespacePrefix + U"Test::TestTemplate<int>");
        }

        SECTION("test template value")
        {
            REQUIRE(NameOf::nameof<Test::TestTemplateValue<Test::B>>() == U"TestTemplateValue<1>");
            REQUIRE(NameOf::nameof_full<Test::TestTemplateValue<Test::B>>() == anonymousNamespacePrefix + U"Test::TestTemplateValue<1>");
        }
    }
}

#endif
