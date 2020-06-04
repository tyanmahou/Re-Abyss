#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::cron
{
    class IJob
    {
    private:
        bool m_isDestroyed = false;
    protected:
        bool m_isActive = true;
        Manager* m_pManager = nullptr;
    public:
        virtual ~IJob() = default;

        virtual void onExecute() = 0;

        void setManager(Manager* const pManager)
        {
            m_pManager = pManager;
        }

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
            m_isDestroyed = true;
        }
        bool isDestroyed() const
        {
            return m_isDestroyed;
        }
    };
}