#include <abyss/components/Event/StageResult/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Cycle/StageResult/Master.hpp>

#include <abyss/utils/Coro/Task/Wait.hpp>

namespace abyss::Event::StageResult
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
    Coro::Task<> MainStream::onExecute()
    {
        co_await Coro::WaitUntil([]{
            return InputManager::A.down();
        });
        m_pEvent->getModule<CycleMaster>()->find<Cycle::StageResult::Master>()->nextScene();
    }
}
