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
        Manager* m_pManager;
    public:
        Events& regist(const std::shared_ptr<Event::IEvent>& event);
        Events& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }
        bool update(double dt);  
        void draw()const;

        bool isEmpty() const;
    };
}