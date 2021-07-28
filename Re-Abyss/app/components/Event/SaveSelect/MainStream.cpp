#include "MainStream.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/UI/SaveSelect/Panel/Builder.hpp>

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
        using namespace UI::SaveSelect;
        auto uis = m_pEvent->getModule<UIs>();

        // パネル作成
        uis->create<Panel::Builder>();
    }
    void MainStream::onEnd()
    {
    }
    Coro::Task<> MainStream::onExecute()
    {
        co_yield{};
    }
}
