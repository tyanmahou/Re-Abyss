#pragma once
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <future>

namespace abyss::Coro
{
    /// <summary>
    /// 指定秒待つ
    /// </summary>
    [[nodiscard]] Task<> WaitForSeconds(const s3d::Duration& duration);

    /// <summary>
    /// 指定秒待つ 時計指定版
    /// </summary>
    [[nodiscard]] Task<> WaitForSeconds(const s3d::Duration& duration, s3d::ISteadyClock* clock);

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

    /// <summary>
    /// 別スレッドで処理し完了するまで待機
    /// </summary>
    template<class Fty, class... Args>
    [[nodiscard]] auto Aysnc(Fty func, Args&&... args)->Task<decltype(func(std::forward<Args>(args)...))>
    {
        auto f = std::async(std::launch::async, std::move(func), std::forward<Args>(args)...);
        while (f.wait_for(0s) != std::future_status::ready) {
            co_yield{};
        }
        co_return f.get();
    }

    /// <summary>
    /// 停止
    /// </summary>
    [[nodiscard]] Task<> Stop();
}