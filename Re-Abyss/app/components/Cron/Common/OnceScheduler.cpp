#include <abyss/components/Cron/Common/OnceScheduler.hpp>

namespace abyss::Cron
{
    Coro::Fiber<> OnceScheduler::execute(std::function<Coro::Fiber<>()> task)
    {
        co_await task();
    }
}
