#include <abyss/components/Event/Home/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>

namespace abyss::Event::Home
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
    void MainStream::onEnd()
    {
    }
    Coro::Fiber<> MainStream::onExecute()
    {
        co_return;
    }
}
