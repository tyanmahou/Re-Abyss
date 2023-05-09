#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/components/Fade/Screen/ScreenFade.hpp>
#include <abyss/components/Fade/IrisOut/IrisOutFade.hpp>

namespace abyss::Fade
{
    /// <summary>
    /// フェードユーティリティ
    /// </summary>
    class FadeUtil
    {
    public:
        /// <summary>
        /// フェードアウトを待機
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> WaitOut(Manager* pManager, const s3d::Optional<s3d::ColorF>& color = s3d::none);
        static Coro::Fiber<> WaitOut(GameObject* pGameObject, const s3d::Optional<s3d::ColorF>& color = s3d::none);

        static std::shared_ptr<IrisOutFade> OutIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec = 1.0);
        /// <summary>
        /// フェードイン待機 プレイヤー座標でアイリスアウト
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> WaitInIrisOutByPlayerPos(Manager* pManager, double timeSec = 1.0);
        static Coro::Fiber<> WaitInIrisOutByPlayerPos(GameObject* pGameObject, double timeSec = 1.0);

        static Coro::Fiber<> WaitInIrisOut(Manager* pManager, std::function<s3d::Vec2()> positionGetter, double timeSec = 1.0);
        static Coro::Fiber<> WaitInIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec = 1.0);

        /// <summary>
        /// フェードアウト待機 プレイヤー座標でアイリスアウト
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> WaitOutIrisOutByPlayerPos(Manager* pManager, double timeSec = 1.0);
        static Coro::Fiber<> WaitOutIrisOutByPlayerPos(GameObject* pGameObject, double timeSec = 1.0);

        static Coro::Fiber<> WaitOutIrisOut(Manager* pManager, std::function<s3d::Vec2()> positionGetter, double timeSec = 1.0);
        static Coro::Fiber<> WaitOutIrisOut(GameObject* pGameObject, const s3d::Vec2& pos, double timeSec = 1.0);
    };
}

namespace abyss
{
    using Fade::FadeUtil;
}
