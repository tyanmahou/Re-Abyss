#include "TalkEvent.hpp"

namespace abyss::Event::Talk
{
    TalkEvent& TalkEvent::addEvent(const std::shared_ptr<IEvent>& event)
    {
        m_events.push(event);
        return *this;
    }
    void TalkEvent::init()
    {}
    bool TalkEvent::update(double dt)
    {
        if (m_events.empty()) {
            return false;
        }
        if (!m_doneCurrentInit) {
            m_events.front()->setManager(m_pManager);
            m_events.front()->init();
            m_doneCurrentInit = true;
        }
        if (!m_events.front()->update(dt)) {
            m_events.pop();
            m_doneCurrentInit = false;
        }
        return true;
    }
    void TalkEvent::draw() const
    {
        if (m_events.empty()) {
            return;
        }
        m_events.front()->draw();
    }

}
