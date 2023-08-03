#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Thread/Task.hpp>

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
            Thread::Task<int> task(Test);
            REQUIRE(task.isValid());

            int result = task.get();
            REQUIRE(result == 1);

            REQUIRE(!task.isValid());
            REQUIRE(!task.isBusy());
        }
        SECTION("test stop")
        {
            Thread::Task<int> task(Test2);
            REQUIRE(task.isBusy());

            task.requestStop();
            int result = task.get();
            REQUIRE(result == 2);

            REQUIRE(!task.isBusy());
        }
        SECTION("test stop2")
        {
            Thread::Task<void> task(Test3);
            REQUIRE(task.isBusy());

            task.requestStop();
            task.get();
            REQUIRE(!task.isBusy());
        }
        SECTION("test deferred")
        {
            Thread::Task<int> task(Test, std::launch::deferred);
            REQUIRE(task.isBusy());

            int result = task.get();
            REQUIRE(result == 1);

            REQUIRE(!task.isBusy());
        }
        SECTION("test timeout")
        {
            Thread::Task<int> task(Test2);
            REQUIRE(task.isBusy());
            REQUIRE(task.isTimeout(1ms));
        }
    }
}
#endif
