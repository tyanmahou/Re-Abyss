#include "MainStream.hpp"

namespace abyss::Event::Talk
{
    MainStream::MainStream(EventObj* pEvent, Ref<Novel::TalkObj> talk):
        m_pEvent(pEvent),
        m_talk(talk)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
    }
    void MainStream::onEnd()
    {
    }
    Coro::Task<> MainStream::onExecute()
    {
        // 会話中はイベントとする
        while (m_talk) {
            co_yield{};
        }
    }
}
