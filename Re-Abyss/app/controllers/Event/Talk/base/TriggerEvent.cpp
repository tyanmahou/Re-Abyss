#include "TriggerEvent.hpp"
#include "TriggerManager.hpp"

namespace abyss::Event::Talk
{
    void TriggerEvent::init()
    {
        auto factory = (*m_triggerManager)[m_triggerName];
        if (!factory) {
            return;
        }
        m_event = factory();
        if (!m_event) {
            return;
        }
        m_event->setManager(this->m_pManager);
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
    void TriggerEvent::onEnd()
    {
        if (!m_event) {
            return;
        }
        m_event->onEnd();
    }
}
