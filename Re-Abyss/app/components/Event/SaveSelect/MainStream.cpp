#include "MainStream.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Event::SaveSelect
{
    MainStream::MainStream(IEvent* pEvent):
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
    Coro::Task<> MainStream::onExecute()
    {
        co_yield{};
    }
}
