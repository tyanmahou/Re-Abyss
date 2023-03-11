#include <abyss/components/UI/Splash/Main.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

#include <abyss/components/UI/Splash/Logo/Builder.hpp>
#include <abyss/components/UI/Splash/Logo/LogoCtrl.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::UI::Splash
{
    Main::Main(UIObj* pUi) :
        m_pUi(pUi)
    {
        m_fiber.reset(std::bind(&Main::onExecute, this));
    }
    void Main::setup([[maybe_unused]]Executer executer)
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
        auto uis = m_pUi->getModule<UIs>();

        // ロゴ生成
        auto pLogo = uis->create<Logo::Builder>();
        auto logoCtrl = pLogo->find<Logo::LogoCtrl>();

        // ロゴ演出待機
        co_await Coro::WaitUntil([&logoCtrl]() {
            return !logoCtrl || logoCtrl->isEnd();
        });

        // シーン遷移
        m_pUi
            ->getModule<CycleMaster>()
            ->find<Cycle::Splash::Master>()
            ->chageOpDemoScene();
    }
}
