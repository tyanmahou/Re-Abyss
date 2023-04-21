#include <abyss/components/Event/GameReady/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/FieldEnv/Environment.hpp>
#include <abyss/modules/Fade/Fader.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::GameReady
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
    Coro::Fiber<> MainStream::onExecute()
    {
        // フェード
        {
            auto* playerManager = m_pEvent->getModule<Actor::Player::PlayerManager>();
            auto* env = m_pEvent->getModule<Environment>();
            auto* camera = m_pEvent->getModule<Camera>();
            auto* fader = m_pEvent->getModule<Fader>();
            auto fade = fader->fadeInIrisOut(camera->transform(playerManager->getPos()));
            fade->setColor(env->getThemeColorOrDefault());
            while (fader->isFading()) {
                fade->setPos(camera->transform(playerManager->getPos()));
                co_yield{};
            }
        }
        co_return;
    }

}
