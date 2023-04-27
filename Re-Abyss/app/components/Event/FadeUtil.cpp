#include <abyss/components/Event/FadeUtil.hpp>

#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Fade/Fader.hpp>

namespace abyss
{
    Coro::Fiber<> FadeUtil::WaitInIrisOutByPlayerPos(Manager* pManager)
    {
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        auto* camera = pManager->getModule<Camera>();
        auto* fader = pManager->getModule<Fader>();
        auto fade = fader->fadeInIrisOut(camera->transform(playerManager->getPos()));
        while (fader->isFading()) {
            fade->setPos(camera->transform(playerManager->getPos()));
            co_yield{};
        }
        co_return;
    }
    Coro::Fiber<> FadeUtil::WaitOutIrisOutByPlayerPos(Manager* pManager)
    {
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        auto* fader = pManager->getModule<Fader>();
        auto* camera = pManager->getModule<Camera>();
        auto fade = fader->fadeOutIrisOut(camera->transform(playerManager->getPos()));
        while (fader->isFading()) {
            fade->setPos(camera->transform(playerManager->getPos()));
            co_yield{};
        }
    }
}
