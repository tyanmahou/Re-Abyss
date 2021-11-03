#include "MainStream.hpp"
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
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
        m_pEvent->getModule<UIs>()->setLayer(UI::Layer::Novel);
    }
    void MainStream::onEnd()
    {
        m_pEvent->getModule<UIs>()->setLayer(UI::Layer::Always);
    }
    Coro::Task<> MainStream::onExecute()
    {
        // 会話中はイベントとする
        while (m_talk) {
            co_yield{};
        }
    }
}
