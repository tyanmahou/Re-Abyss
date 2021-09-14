#include "TalkCtrl.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>

namespace abyss::Event::Talk
{
    TalkCtrl::TalkCtrl(EventObj* pEvent):
        m_pEvent(pEvent)
    {}

    void TalkCtrl::setup([[maybe_unused]]Executer executer)
    {
    }

    void TalkCtrl::onStart()
    {

    }
    void TalkCtrl::onEnd()
    {
        // 残りのイベントを処理する
        while (!m_talks.empty()) {
            auto& front = m_talks.front();
            if (!m_doneCurrentInit) {
                front->setup();
                front->start();
                m_doneCurrentInit = true;
            }
            front->end();
            m_talks.pop();
            m_doneCurrentInit = false;
        }
    }

    Coro::Task<> TalkCtrl::onExecute()
    {
        while (!m_talks.empty()) {
            if (InputManager::Start.down()) {
                // skip
                co_return;
            }

            auto& front = m_talks.front();
            if (!m_doneCurrentInit) {
                front->setup();
                front->start();
                m_doneCurrentInit = true;
            }

            if (!front->update()) {
                front->end();
                m_talks.pop();
                m_doneCurrentInit = false;
            }

            co_yield{};
        }
        co_return;
    }

    Ref<TalkObj> TalkCtrl::create()
    {
        return this->regist(std::make_shared<TalkObj>(m_pEvent));
    }

    Ref<TalkObj> TalkCtrl::regist(const std::shared_ptr<TalkObj>& talk)
    {
        talk->setManager(m_pEvent->getManager());
        m_talks.push(talk);
        return talk;
    }
}

