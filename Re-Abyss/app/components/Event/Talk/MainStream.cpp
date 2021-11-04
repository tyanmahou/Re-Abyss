#include "MainStream.hpp"
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Novel/Novels.hpp>
#include <abyss/components/Novel/TalkBuilder.hpp>

namespace abyss::Event::Talk
{
    MainStream::MainStream(EventObj* pEvent, const s3d::String& path):
        m_pEvent(pEvent),
        m_path(path)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
        m_talk = m_pEvent->getModule<Novels>()->create<Novel::TalkBuilder>(m_path);
        m_pEvent->getModule<UIs>()->setFilter(UI::Filter::Novel);
    }
    void MainStream::onEnd()
    {
        m_pEvent->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Task<> MainStream::onExecute()
    {
        // 会話中はイベントとする
        while (m_talk) {
            co_yield{};
        }
    }
}
