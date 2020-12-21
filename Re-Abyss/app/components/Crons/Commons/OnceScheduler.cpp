#include "OnceScheduler.hpp"

namespace abyss::cron
{
    Coro::Task<> OnceScheduler::execute(std::function<Coro::Task<>()> task)
    {
        co_yield task();
    }
}
