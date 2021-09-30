#include "MainStream.hpp"

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

#include <abyss/components/Event/Common/FadeIrisOut.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::GameRestart
{
    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<FadeIrisOut>();
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
    Coro::Task<> MainStream::onExecute()
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
            auto fade = m_pEvent->find<FadeIrisOut>();
            fade->create();
            auto playerManager = m_pEvent->getModule<Actor::Player::PlayerManager>();

            Timer timer(1s, StartImmediately::Yes);

            while (!timer.reachedZero()) {
                fade->setPos(playerManager->getPos())
                    .setFadeTime(timer.progress0_1())
                    ;
                co_yield{};
            }
        }
    }

    double MainStream::getGlobalTimeScale() const
    {
        return m_globalTimeScale;
    }

}
