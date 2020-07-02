#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Event
{
    class IEvent
    {
    protected:
        Manager* m_pManager = nullptr;
    public:
        virtual ~IEvent() = default;
        void setManager(Manager* manager)
        {
            m_pManager = manager;
        }
        virtual void onStart(){}
        virtual bool update(double dt) = 0;
        virtual void onEnd(){}
    };
}