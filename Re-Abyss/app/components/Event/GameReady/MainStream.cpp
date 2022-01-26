#include <abyss/components/Event/GameReady/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>

#include <abyss/components/Event/Common/FadeIrisOut.hpp>


#include <Siv3D.hpp>

namespace abyss::Event::GameReady
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
        m_pEvent->find<FadeIrisOut>()->setIsFadeIn(true);
    }
    Coro::Task<> MainStream::onExecute()
    {
        // フェード
        {
            auto fade = m_pEvent->find<FadeIrisOut>();

            auto globalTime = m_pEvent->getModule<GlobalTime>();
            auto playerManager = m_pEvent->getModule<Actor::Player::PlayerManager>();

            s3d::Timer timer(1s, s3d::StartImmediately::Yes, globalTime);

            while (!timer.reachedZero()) {
                fade->setPos(playerManager->getPos())
                    .setFadeTime(timer.progress0_1())
                    ;
                co_yield{};
            }
        }
        co_return;
    }

}
