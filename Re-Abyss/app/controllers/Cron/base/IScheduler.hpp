#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::cron
{
    class IJob;

    class IScheduler
    {
    protected:
        Manager* m_pManager = nullptr;
    public:
        virtual ~IScheduler() = default;
        void setManager(Manager* const pManager)
        {
            m_pManager = pManager;
        }

        virtual Coro::Task<> execute(IJob* job) = 0;
    };
}