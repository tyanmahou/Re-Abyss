#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Event
{
    class IEvent
    {
    protected:
        Manager* m_pManager;
    public:
        virtual ~IEvent() = default;
        void setManager(Manager* manager)
        {
            m_pManager = manager;
        }
        virtual void init(){}
        virtual bool update(double dt) = 0;
        virtual void draw()const {}
    };
}