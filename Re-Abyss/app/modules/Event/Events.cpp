#include "Events.hpp"

namespace abyss
{
    bool Events::init()
    {
        if (m_events.empty()) {
            return false;
        }
        auto& front = m_events.front();
        front->setup();
        front->start();
        m_doneCurrentInit = true;
        return true;
    }

    bool Events::update()
    {
        do {
            if (m_events.empty()) {
                return false;
            }
            auto& front = m_events.front();
            if (!m_doneCurrentInit) {
                front->setup();
                front->start();
                m_doneCurrentInit = true;
            }
            if (!front->update()) {
                front->end();
                m_events.pop();
                m_doneCurrentInit = false;
            }
        } while (!m_doneCurrentInit);

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
    Ref<Event::IEvent> Events::create()
    {
        return this->regist(std::make_shared<Event::IEvent>());
    }

    Ref<Event::IEvent> Events::regist(const std::shared_ptr<Event::IEvent>& event)
    {
        event->setManager(m_pManager);
        m_events.push(event);
        return event;
    }
}
