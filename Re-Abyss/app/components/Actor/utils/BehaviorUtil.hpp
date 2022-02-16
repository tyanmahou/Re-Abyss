#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

#include <Siv3D/Fwd.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Actor
{
    struct BehaviorUtil
    {
        /// <summary>
        /// 指定秒待つ
        /// </summary>
        /// <param name="pActor"></param>
        /// <param name="sec"></param>
        /// <returns></returns>
        [[nodiscard]] static Coro::Task<> WaitForSeconds(ActorObj* pActor, double sec);
        [[nodiscard]] static Coro::Task<> WaitForSeconds(ActorObj* pActor, s3d::Duration duration);

        /// <summary>
        /// 停止
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] static Coro::Task<> Freeze();

        /// <summary>
        /// HPがrate割合以下になったか
        /// </summary>
        /// <param name="pActor"></param>
        /// <param name="rate"></param>
        /// <returns></returns>
        [[nodiscard]] static Coro::Task<> WaitLessThanHpRate(ActorObj* pActor, double rate);
    };
}