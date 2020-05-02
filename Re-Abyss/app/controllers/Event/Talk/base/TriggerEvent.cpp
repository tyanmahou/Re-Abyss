#include "TriggerEvent.hpp"
#include "TriggerManager.hpp"

namespace abyss::Event::Talk
{
    void TriggerEvent::init()
    {
        m_event = (*m_triggerManager)[m_triggerName];
        (*m_triggerManager)[m_triggerName] = nullptr;
        if (!m_event) {
            return;
        }
        m_event->init();
    }
    bool TriggerEvent::update(double dt)
    {
        if (!m_event) {
            return false;
        }
        return m_event->update(dt);
    }
    void TriggerEvent::draw() const
    {
        if (!m_event) {
            return;
        }
        return m_event->draw();
    }
}
