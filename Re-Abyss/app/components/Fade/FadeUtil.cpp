#include <abyss/components/Fade/FadeUtil.hpp>

#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace
{
    using namespace abyss::Fade;
    template<FadeOperation Operation>
    void FadeInOut(Fader* pFader, double timeSec)
    {
        if constexpr (Operation == FadeOperation::FadeIn) {
            pFader->fadeIn(timeSec);
        } else {
            pFader->fadeOut(timeSec);
        }
    }
}
namespace abyss::Fade
{
    template<FadeOperation Operation>
    std::shared_ptr<ScreenFade> FadeUtil<Operation>::Screen(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color, double timeSec)
    {
        auto* fader = pGameObject->getModule<Fader>();
        auto fade = fader->create<ScreenFade>();
        if (color) {
            fade->setColor(*color);
        }
        ::FadeInOut<Operation>(fader, timeSec);
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
    std::shared_ptr<IrisOutFade> FadeUtil<Operation>::IrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec)
    {
        auto* camera = pGameObject->getModule<Camera>();
        auto* fader = pGameObject->getModule<Fader>();
        auto fade = fader->create<IrisOutFade>();
        fade->setPos(camera->transform(pos));
        ::FadeInOut<Operation>(fader, timeSec);
        return fade;
    }
    template<FadeOperation Operation>
    Coro::Fiber<> FadeUtil<Operation>::WaitIrisOutByPlayerPos(GameObject* pGameObject, double timeSec)
    {
        auto* playerManager = pGameObject->getModule<Actor::Player::PlayerManager>();
        return WaitIrisOut(pGameObject, [playerManager] {
            return playerManager->getPos();
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
