#pragma once

#include <Siv3D/Duration.hpp>
#include <abyss/utils/Time/Time.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Coro
{
    /// <summary>
    /// 指定秒待つ
    /// </summary>
    [[nodiscard]] Task<> WaitForSeconds(const s3d::Duration& duration);

    /// <summary>
    /// 指定病待つ 時計指定版
    /// </summary>
    [[nodiscard]] Task<> WaitForSecondsEx(const s3d::Duration& duration, TimeGetFunction_t timeGetter = Time::GetNow);

    /// <summary>
    /// 指定フレーム待つ
    /// </summary>
    [[nodiscard]] Task<> WaitForFrame(s3d::int32 frame);

    /// <summary>
    /// 条件をみたすまで待つ
    /// </summary>
    template<class Pred, std::enable_if_t<std::is_invocable_r_v<bool, Pred>>* = nullptr>
    [[nodiscard]] Task<> WaitUntil(Pred pred)
    {
        while (!pred()) {
            co_yield{};
        }
    }

    /// <summary>
    /// 条件をみたす間待つ
    /// </summary>
    template<class Pred, std::enable_if_t<std::is_invocable_r_v<bool, Pred>>* = nullptr>
    [[nodiscard]] Task<> WaitWhile(Pred pred)
    {
        while (pred()) {
            co_yield{};
        }
    }
}