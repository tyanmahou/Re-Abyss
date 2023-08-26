#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Thread/Task.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::tests
{
    namespace {
        int Test()
        {
            return 1;
        }
        int Test2(std::stop_token token)
        {
            while (!token.stop_requested())
            {
                std::this_thread::sleep_for(3ms);
            }
            return 2;
        }
        void Test3(std::stop_token token)
        {
            while (!token.stop_requested())
            {
                std::this_thread::sleep_for(3ms);
            }
        }
        Coro::Fiber<int> Coroutine(std::launch policy)
        {
            int result = co_await Thread::Task(policy, [] {return 3; });
            co_return result;
        }
    }
    TEST_CASE("utils::Thread::Task. Test")
    {
        SECTION("test invalid")
        {
            Thread::Task<void> task;
            REQUIRE(!task.isValid());
        }
        SECTION("test normal")
        {
            Thread::Task task(Test);
            REQUIRE(task.isValid());

            int result = task.get();
            REQUIRE(result == 1);

            REQUIRE(!task.isValid());
            REQUIRE(!task.isBusy());
        }
        SECTION("test stop")
        {
            Thread::Task task(Test2);
            REQUIRE(task.isBusy());

            task.request_stop();
            int result = task.get();
            REQUIRE(result == 2);

            REQUIRE(!task.isBusy());
        }
        SECTION("test stop")
        {
            Thread::Task task(Test3);
            REQUIRE(task.isBusy());

            task.request_stop();
            task.get();
            REQUIRE(!task.isBusy());
        }
        SECTION("test stop 2")
        {
            std::stop_source source;
            Thread::Task task(source, Test3);
            REQUIRE(task.isBusy());

            source.request_stop();
            task.get();
            REQUIRE(!task.isBusy());
        }
        SECTION("test stop token")
        {
            Thread::Task task(Test3);
            REQUIRE(task.isBusy());

            auto token = task.get_token();
            REQUIRE(!token.stop_requested());
            task.request_stop();
            REQUIRE(token.stop_requested());
        }
        SECTION("test deferred")
        {
            Thread::Task task(std::launch::deferred, Test);
            REQUIRE(!task.isBusy());

            int result = task.get();
            REQUIRE(result == 1);

            REQUIRE(!task.isBusy());
        }
        SECTION("test timeout")
        {
            Thread::Task task(Test2);
            REQUIRE(task.isBusy());
            REQUIRE(task.isTimeout(1ms));
        }
        SECTION("test coroutine")
        {
            auto fiber = Coroutine(std::launch::async);
            while (fiber.resume())
            {
                std::this_thread::sleep_for(1ms);
            }
            REQUIRE(fiber.get() == 3);
        }
        SECTION("test coroutine deferred")
        {
            auto fiber = Coroutine(std::launch::deferred);
            while (fiber.resume())
            {
                std::this_thread::sleep_for(1ms);
            }
            REQUIRE(fiber.get() == 3);
        }
    }
}
#endif
