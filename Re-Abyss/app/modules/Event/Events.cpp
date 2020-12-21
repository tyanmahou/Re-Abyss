#include "Events.hpp"

namespace abyss
{
    bool Events::init()
    {
        if (m_events.empty()) {
            return false;
        }
        m_events.front()->onStart();
        m_doneCurrentInit = true;
        return true;
    }

    Events& Events::regist(const std::shared_ptr<Event::IEvent>& event)
    {
        event->setManager(m_pManager);
        m_events.push(event);
        return *this;
    }

    bool Events::update(double dt)
    {
        if (m_events.empty()) {
            return false;
        }
        if (!m_doneCurrentInit) {
            m_events.front()->onStart();
            m_doneCurrentInit = true;
        }
        if (!m_events.front()->update(dt)) {
            m_events.front()->onEnd();
            m_events.pop();
            m_doneCurrentInit = false;
            return this->update(dt);
        }
        return true;

    }

    bool Events::isEmpty() const
    {
        return m_events.empty();
    }

    bool Events::isWorldStop() const
    {
        return !m_events.empty() && m_events.front()->isWorldStop();
    }
}
