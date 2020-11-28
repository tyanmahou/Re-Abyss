#pragma once

#include <Siv3D/Duration.hpp>
#include <abyss/utils/Time/Time.hpp>

namespace abyss::Coro
{
    struct Task;

    /// <summary>
    /// 指定秒待つ
    /// </summary>
    Task WaitForSeconds(const s3d::Duration& duration);

    /// <summary>
    /// 指定病待つ 時計指定版
    /// </summary>
    Task WaitForSecondsEx(const s3d::Duration& duration, TimeGetFunction_t timeGetter = Time::GetNow);

    /// <summary>
    /// 指定フレーム待つ
    /// </summary>
    Task WaitForFrame(s3d::int32 frame);
}