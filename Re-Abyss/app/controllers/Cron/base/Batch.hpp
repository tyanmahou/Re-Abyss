#pragma once
#include <memory>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/controllers/Cron/base/IJob.hpp>
#include <abyss/controllers/Cron/base/IScheduler.hpp>

namespace abyss::cron
{
    class IJob;
    class IScheduler;

    class Batch
    {
        std::shared_ptr<IJob> m_job;
        std::shared_ptr<IScheduler> m_scheduler;
        bool m_isActive = true;
        bool m_isDesroyed = false;
        Coro::Task<> m_task;

        Coro::Task<> execute();
    public:
        Batch(std::shared_ptr<IJob> job, std::shared_ptr<IScheduler> scheduer);

        bool update();

        void setActive(bool active)
        {
            m_isActive = active;
        }
        bool isActive() const
        {
            return m_isActive;
        }

        void destroy()
        {
            m_isDesroyed = true;
        }
        bool isDestroyed() const
        {
            return m_isDesroyed;
        }
    };
}