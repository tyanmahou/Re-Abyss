#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::cron
{
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

        virtual void start() {}
        virtual bool update(double dt) = 0;
    };
}