#include "OnceScheduler.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <abyss/modules/Cron/base/IJob.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
namespace abyss::cron
{
    Coro::Task<> OnceScheduler::execute(IJob* job)
    {
        co_yield job->onExecute();
    }
}
