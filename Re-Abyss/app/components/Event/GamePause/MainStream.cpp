#include <abyss/components/Event/GamePause/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Event::GamePause
{
    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
        m_pEvent->getModule<GlobalTime>()->pause();
    }
    void MainStream::onEnd()
    {
        m_pEvent->getModule<GlobalTime>()->resume();
    }
    Coro::Task<> MainStream::onExecute()
    {
        // 1フレーム待ち
        co_yield{};

        while (true) {
            if (InputManager::Start.down()) {
                co_return;
            }
            co_yield{};
        }
    }

}
