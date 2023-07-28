#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::tests
{
    namespace {
        Coro::Fiber<int> Test(int* a)
        {
            *a = 1;
            co_yield{};
            co_await Coro::WaitForFrame(2);
            *a = 2;
            co_yield{};
            *a = 3;
            *a = 4;
            co_return *a + 1;
        }
    }
    TEST_CASE("utils::Coro::Fiber. Test")
    {
        SECTION("test normal")
        {
            int a = 0;
            auto fiber = Test(&a);
            REQUIRE(a == 0);
            fiber.resume();
            REQUIRE(a == 1);
            fiber.resume();
            REQUIRE(a == 1);
            fiber.resume();
            REQUIRE(a == 1);
            fiber.resume();
            REQUIRE(a == 2);
            fiber.resume();
            REQUIRE(a == 4);
            REQUIRE(fiber.get() == 5);
            REQUIRE(fiber.isDone());
        }
    }
}
#endif
