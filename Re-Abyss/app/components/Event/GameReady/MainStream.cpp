#include <abyss/components/Event/GameReady/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Fade/FadeUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::GameReady
{
    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
    }
    Coro::Fiber<> MainStream::onExecute()
    {
        // フェード
        co_await FadeIn::WaitIrisOutByPlayerPos(m_pEvent);
    }

}
