#include <abyss/components/Event/Splash/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

#include <abyss/components/UI/Splash/Logo/Builder.hpp>
#include <abyss/components/UI/Splash/Logo/LogoCtrl.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>

#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Event::Splash
{
    using namespace UI::Splash;

    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
        auto uis = m_pEvent->getModule<UIs>();

        // ロゴ生成
        m_pLogo = uis->create<Logo::Builder>();
    }
    void MainStream::onEnd()
    {
    }
    Coro::Task<> MainStream::onExecute()
    {
        auto logoCtrl = m_pLogo->find<Logo::LogoCtrl>();

        // ロゴ演出待機
        co_await Coro::WaitUntil([&logoCtrl]() {
            return !logoCtrl || logoCtrl->isEnd();
        });

        // シーン遷移
        m_pEvent
            ->getModule<CycleMaster>()
            ->find<Cycle::Splash::Master>()
            ->chageOpDemoScene();
    }
}
