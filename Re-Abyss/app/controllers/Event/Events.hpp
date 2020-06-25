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

        bool init();

        Events& regist(const std::shared_ptr<Event::IEvent>& event);

        template<class T, class... Args>
        Events& create(Args&&... args)
        {
            auto event = std::make_shared<T>(std::forward<Args>(args)...);
            return regist(event);
        }

        Events& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }
        bool update(double dt);  

        bool isEmpty() const;
    };
}