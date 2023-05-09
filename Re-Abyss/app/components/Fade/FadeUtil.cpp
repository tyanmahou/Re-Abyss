#include <abyss/components/Fade/FadeUtil.hpp>

#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Fade
{
    Coro::Fiber<> FadeUtil::WaitOut(Manager* pManager, const s3d::Optional<s3d::ColorF>& color)
    {
        auto* fader = pManager->getModule<Fader>();
        auto fade = fader->fadeOutScreen(1.0);

        if (color) {
            fade->setColor(*color);
        }
        while (fader->isFading()) {
            co_yield{};
        }
        co_return;
    }
    Coro::Fiber<> FadeUtil::WaitOut(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color)
    {
        return WaitOut(pGameObject->getManager(), color);
    }
    Coro::Fiber<> FadeUtil::WaitInIrisOutByPlayerPos(Manager* pManager, double timeSec)
    {
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        return WaitInIrisOut(pManager, [playerManager]{
            return playerManager->getPos();
        }, timeSec);
    }
    Coro::Fiber<> FadeUtil::WaitInIrisOutByPlayerPos(GameObject* pGameObject, double timeSec)
    {
        return WaitInIrisOutByPlayerPos(pGameObject->getManager(),timeSec);
    }
    Coro::Fiber<> FadeUtil::WaitInIrisOut(Manager* pManager, std::function<s3d::Vec2()> positionGetter, double timeSec)
    {
        auto* camera = pManager->getModule<Camera>();
        auto* fader = pManager->getModule<Fader>();
        auto fade = fader->fadeInIrisOut(camera->transform(positionGetter()), timeSec);
        while (fader->isFading()) {
            fade->setPos(camera->transform(positionGetter()));
            co_yield{};
        }
        co_return;
    }
    Coro::Fiber<> FadeUtil::WaitInIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec)
    {
        return WaitInIrisOut(pGameObject->getManager(), [pos] {
            return pos;
        }, timeSec);
    }
    Coro::Fiber<> FadeUtil::WaitOutIrisOutByPlayerPos(Manager* pManager, double timeSec)
    {
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        return WaitOutIrisOut(pManager, [playerManager] {
            return playerManager->getPos();
        }, timeSec);
    }
    Coro::Fiber<> FadeUtil::WaitOutIrisOutByPlayerPos(GameObject* pGameObject, double timeSec)
    {
        return WaitOutIrisOutByPlayerPos(pGameObject->getManager(), timeSec);
    }
    Coro::Fiber<> FadeUtil::WaitOutIrisOut(Manager* pManager, std::function<s3d::Vec2()> positionGetter, double timeSec)
    {
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        auto* fader = pManager->getModule<Fader>();
        auto* camera = pManager->getModule<Camera>();
        auto fade = fader->fadeOutIrisOut(camera->transform(playerManager->getPos()), timeSec);
        while (fader->isFading()) {
            fade->setPos(camera->transform(playerManager->getPos()));
            co_yield{};
        }
    }
    Coro::Fiber<> FadeUtil::WaitOutIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec)
    {
        return WaitOutIrisOut(pGameObject->getManager(), [pos] {
            return pos;
        }, timeSec);
    }
}
