#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/components/Fade/Screen/ScreenFade.hpp>
#include <abyss/components/Fade/IrisOut/IrisOutFade.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Fade
{
    enum class FadeOperation
    {
        FadeIn,
        FadeOut,
    };

    template<FadeOperation Operation>
    class FadeUtil
    {
    public:
        /// <summary>
        /// スクリーンフェード
        /// </summary>
        /// <param name="pGameObject"></param>
        /// <param name="pos"></param>
        /// <param name="color"></param>
        /// <param name="timeSec"></param>
        /// <returns></returns>
        static Ref<ScreenFade> Screen(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color = s3d::none, double timeSec = 1.0);
        static Coro::Fiber<> WaitScreen(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color = s3d::none, double timeSec = 1.0);

        /// <summary>
        /// アイリスアウト
        /// </summary>
        /// <param name="pGameObject"></param>
        /// <param name="pos"></param>
        /// <param name="timeSec"></param>
        /// <returns></returns>
        static Ref<IrisOutFade> IrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec = 1.0);
        static Coro::Fiber<> WaitIrisOutByPlayerPos(GameObject* pGameObject, double timeSec = 1.0);
        static Coro::Fiber<> WaitIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec = 1.0);
        static Coro::Fiber<> WaitIrisOut(GameObject* pGameObject, std::function<s3d::Vec2()> positionGetter, double timeSec = 1.0);
    };
}

namespace abyss
{
    using FadeIn = Fade::FadeUtil<Fade::FadeOperation::FadeIn>;
    using FadeOut = Fade::FadeUtil<Fade::FadeOperation::FadeOut>;
}
