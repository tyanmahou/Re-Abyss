#include <abyss/components/UI/StageResult/Main.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Cycle/StageResult/Master.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::UI::StageResult
{
    Main::Main(UIObj* pUi) :
        m_pUi(pUi)
    {
        m_fiber.reset(std::bind(&Main::onExecute, this));
    }
    void Main::setup([[maybe_unused]] Executer executer)
    {
    }
    void Main::onStart()
    {
    }
    void Main::onEnd()
    {
    }
    void Main::onUpdate()
    {
        m_fiber.resume();
    }
    Coro::Fiber<> Main::onExecute()
    {
        co_await Coro::FiberUtil::WaitUntil([] {
            return InputManager::A.down();
        });
        m_pUi->getModule<CycleMaster>()->find<Cycle::StageResult::Master>()->nextScene();
    }
}
