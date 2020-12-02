#include "Batch.hpp"

namespace abyss::cron
{
    Batch::Batch(std::shared_ptr<IJob> job, std::shared_ptr<IScheduler> scheduer):
        m_job(job),
        m_scheduler(scheduer),
        m_task(execute())
    {}

    bool Batch::update()
    {
        return m_task.moveNext();
    }

    Coro::Task<> Batch::execute()
    {
        co_yield m_scheduler->execute(m_job.get());
    }
}
