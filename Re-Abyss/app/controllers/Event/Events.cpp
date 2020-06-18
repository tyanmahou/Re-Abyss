#include "Events.hpp"

namespace abyss
{
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
            m_events.front()->init();
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

    void Events::draw() const
    {
        if (m_events.empty()) {
            return;
        }
        m_events.front()->draw();
    }
    bool Events::isEmpty() const
    {
        return m_events.empty();
    }
}
