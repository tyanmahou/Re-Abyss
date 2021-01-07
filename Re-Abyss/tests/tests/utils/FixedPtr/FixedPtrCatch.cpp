#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/FixedPtr/FixedPtr.hpp>

namespace
{
    struct DeleteTest
    {
        int& a;
        DeleteTest(int& a)
            :a(a)
        {}
        ~DeleteTest()
        {
            ++a;
        }
    };

    struct Super
    {
        virtual int func()const = 0;
    };
    struct A : virtual Super
    {
        int func()const override
        {
            return 1;
        }
    };
    struct B : virtual Super
    {
        int func()const override
        {
            return 2;
        }
    };
    struct C : A, B
    {
        int func()const override
        {
            return 3;
        }
    };
    struct D : A
    {
    };
}
namespace abyss::tests
{
    TEST_CASE("utils::FixedPtr. Test")
    {
        SECTION("delete test")
        {
            int a = 0;
            {
                fixed_ptr<DeleteTest> ptr;
                ptr = new DeleteTest(a);
                REQUIRE(a == 0);

                // ここで破棄された
                ptr = nullptr;
                REQUIRE(a == 1);


                fixed_ptr<DeleteTest> ptr2;
                ptr2 = new DeleteTest(a);

                // 所有権は共有
                auto ptr3 = ptr2;
            }
            REQUIRE(a == 2);
        }

        SECTION("dynamic_cast test")
        {
            using PtrType = fixed_ptr<Super, A, B>;

            PtrType ptr(new A{});

            REQUIRE(fixed_dynamic_cast<Super*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<A*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<B*>(ptr) == nullptr);
        }
        SECTION("dynamic_cast by 2 extends")
        {
            using PtrType = fixed_ptr<Super, A, B>;

            PtrType ptr(new C{});

            REQUIRE(fixed_dynamic_cast<Super*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<A*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<B*>(ptr) != nullptr);
        }
        SECTION("dynamic_cast by multi extends")
        {
            using PtrType = fixed_ptr<Super, A, B>;

            PtrType ptr(new D{});

            REQUIRE(fixed_dynamic_cast<Super*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<A*>(ptr) != nullptr);
            REQUIRE(fixed_dynamic_cast<B*>(ptr) == nullptr);
        }
        SECTION("call func")
        {
            using PtrType = fixed_ptr<Super, A, B>;

            PtrType ptr(new A{});

            REQUIRE(ptr->func() == 1);

            PtrType ptr2(new B{});

            REQUIRE(ptr2->func() == 2);
        }
    }
}
#endif