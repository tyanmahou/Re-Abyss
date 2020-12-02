#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Coro
{
    template<class T =void>
    struct  Task;
}
namespace abyss::cron
{
    class IJob
    {
    protected:
        Manager* m_pManager = nullptr;
    public:
        virtual ~IJob() = default;

        virtual Coro::Task<> onExecute() = 0;

        void setManager(Manager* const pManager)
        {
            m_pManager = pManager;
        }
    };
}