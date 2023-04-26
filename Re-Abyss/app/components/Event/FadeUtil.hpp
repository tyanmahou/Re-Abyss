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
        /// アイリスアウト フェードイン
        /// </summary>
        /// <param name="pManager"></param>
        /// <returns></returns>
        static Coro::Fiber<> FadeInIrisOutByPlayerPos(Manager* pManager);
    };
}
