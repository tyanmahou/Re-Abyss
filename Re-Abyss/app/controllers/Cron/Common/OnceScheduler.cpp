#include "OnceScheduler.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

#include <abyss/controllers/Cron/base/IJob.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
namespace abyss::cron
{
    Coro::Task<> OnceScheduler::execute(IJob* job)
    {
        co_yield job->onExecute();
    }
}
