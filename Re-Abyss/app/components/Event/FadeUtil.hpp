#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss
{
    /// <summary>
    /// フェードユーティリティ
    /// </summary>
    class FadeUtil
    {
    public:
        /// <summary>
        /// フェードイン待機 プレイヤー座標でアイリスアウト
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> WaitInIrisOutByPlayerPos(Manager* pManager);

        /// <summary>
        /// フェードアウト待機 プレイヤー座標でアイリスアウト
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> WaitOutIrisOutByPlayerPos(Manager* pManager);
    };
}
