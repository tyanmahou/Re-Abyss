#include "OnceScheduler.hpp"

namespace abyss::Cron
{
    Coro::Task<> OnceScheduler::execute(std::function<Coro::Task<>()> task)
    {
        co_await task();
    }
}
