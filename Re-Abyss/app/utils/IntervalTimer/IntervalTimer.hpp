#pragma once
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss
{
    class IntervalTimer
    {
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;

    public:
        IntervalTimer(double timeSec = 0.0, bool startImmediately = false, TimeGetFunction_t timeGetter = Time::GetNow);

        IntervalTimer(const s3d::Duration& time, bool startImmediately = false, TimeGetFunction_t timeGetter = Time::GetNow);

        /// <summary>
        /// タイマー更新
        /// </summary>
        /// <returns>リスタート時にtrue</returns>
        bool update() const;

        /// <summary>
        /// リスタートしたフレームでtrue
        /// </summary>
        /// <returns></returns>
        bool onRestart() const;
    };
}