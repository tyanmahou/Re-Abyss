#include "TalkEvent.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Event::Talk
{
    TalkEvent& TalkEvent::addEvent(const std::shared_ptr<IEvent>& event)
    {
        m_events.push(event);
        return *this;
    }
    void TalkEvent::init()
    {    
    }
    bool TalkEvent::update(double dt)
    {
        if (m_events.empty()) {
            return false;
        }
        if (InputManager::Start.down()) {
            // skip
            return false;
        }
        if (!m_doneCurrentInit) {
            m_events.front()->setManager(m_pManager);
            m_events.front()->init();
            m_doneCurrentInit = true;
        }
        if (!m_events.front()->update(dt)) {
            m_events.front()->onEnd();
            m_events.pop();
            m_doneCurrentInit = false;
        }
        return true;
    }

    void TalkEvent::onEnd()
    {
        // 残りのイベントを処理する
        while (!m_events.empty()) {
            if (!m_doneCurrentInit) {
                m_events.front()->setManager(m_pManager);
                m_events.front()->init();
                m_doneCurrentInit = true;
            }
            m_events.front()->onEnd();
            m_events.pop();
            m_doneCurrentInit = false;
        }
    }

}
