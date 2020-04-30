#pragma once
#include <queue>
#include <memory>
#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class Events
    {
    private:
        std::queue<std::shared_ptr<Event::IEvent>> m_events;
        bool m_doneCurrentInit = false;
        ActManager* m_pManager;
    public:
        Events& regist(const std::shared_ptr<Event::IEvent>& event);
        Events& setManager(ActManager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }
        bool update(double dt);  
        void draw()const;
    };
}