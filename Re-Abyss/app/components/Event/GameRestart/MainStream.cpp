#include <abyss/components/Event/GameRestart/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::GameRestart
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
        // リスタート
        m_pEvent->getModule<CycleMaster>()
            ->find<Cycle::Main::Master>()
            ->restart();
    }
    Coro::Fiber<> MainStream::onExecute()
    {
        // スローモーション
        {
            Timer timer(2.5s, StartImmediately::Yes);
            while (!timer.reachedZero()) {
                m_globalTimeScale = timer.progress0_1();
                co_yield{};
            }

            m_globalTimeScale = 1.0;
        }
        // フェード
        {
            auto* playerManager = m_pEvent->getModule<Actor::Player::PlayerManager>();
            auto* fader = m_pEvent->getModule<Fader>();
            auto* camera = m_pEvent->getModule<Camera>();
            auto fade = fader->fadeOutIrisOut(camera->transform(playerManager->getPos()));
            while (fader->isFading()) {
                fade->setPos(camera->transform(playerManager->getPos()));
                co_yield{};
            }
        }
    }

    double MainStream::getGlobalTimeScale() const
    {
        return m_globalTimeScale;
    }

}
