#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Event
{
    class IEvent
    {
    protected:
        ActManager* m_pManager;
    public:
        void setManager(ActManager* manager)
        {
            m_pManager = manager;
        }
        virtual void init(){};
        virtual bool update(double dt) = 0;
        virtual void draw()const {};
    };
}