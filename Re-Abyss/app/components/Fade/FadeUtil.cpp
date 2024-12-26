#include <abyss/components/Fade/FadeUtil.hpp>

#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Fade;
    template<FadeOperation Operation, class T>
    Ref<T> FadeInOut(GameObject* pGameObject, double timeSec)
    {
        auto* pFader = pGameObject->getModule<Fader>();
        if constexpr (Operation == FadeOperation::FadeIn) {
            pFader->fadeIn(timeSec);
        } else {
            pFader->fadeOut(timeSec);
        }
        return pFader->set<T>();
    }
}
namespace abyss::Fade
{
    template<FadeOperation Operation>
    Ref<ScreenFade> FadeUtil<Operation>::Screen(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color, double timeSec)
    {
        auto fade = ::FadeInOut<Operation, ScreenFade>(pGameObject, timeSec);
        if (color) {
            fade->setColor(*color);
        }
        return fade;
    }
    template<FadeOperation Operation>
    Coro::Fiber<> FadeUtil<Operation>::WaitScreen(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color, double timeSec)
    {
        Screen(pGameObject, color, timeSec);
        auto* fader = pGameObject->getModule<Fader>();
        while (fader->isFading()) {
            co_yield{};
        }
        co_return;
    }
    template<FadeOperation Operation>
    Ref<IrisOutFade> FadeUtil<Operation>::IrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec)
    {
        auto fade = ::FadeInOut<Operation, IrisOutFade>(pGameObject, timeSec);
        auto* camera = pGameObject->getModule<Camera>();
        fade->setPos(camera->transform(pos));
        return fade;
    }
    template<FadeOperation Operation>
    Coro::Fiber<> FadeUtil<Operation>::WaitIrisOutByPlayerPos(GameObject* pGameObject, double timeSec)
    {
        auto* playerManager = pGameObject->getModule<Actor::Player::PlayerManager>();
        return WaitIrisOut(pGameObject, [playerManager] {
            return playerManager->getCenterPos();
        }, timeSec);
    }
    template<FadeOperation Operation>
    Coro::Fiber<> FadeUtil<Operation>::WaitIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec)
    {
        return WaitIrisOut(pGameObject, [pos] {
            return pos;
        }, timeSec);
    }
    template<FadeOperation Operation>
    Coro::Fiber<> FadeUtil<Operation>::WaitIrisOut(GameObject* pGameObject, std::function<s3d::Vec2()> positionGetter, double timeSec)
    {
        auto fade = IrisOut(pGameObject, positionGetter(), timeSec);

        auto* fader = pGameObject->getModule<Fader>();
        auto* camera = pGameObject->getModule<Camera>();
        while (fader->isFading()) {
            fade->setPos(camera->transform(positionGetter()));
            co_yield{};
        }
    }
    template class FadeUtil<FadeOperation::FadeIn>;
    template class FadeUtil<FadeOperation::FadeOut>;
}
