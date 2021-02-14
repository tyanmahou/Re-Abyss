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
        IntervalTimer(double timeSec = 0.0, bool startImmediately = false, Clock_t timeGetter = Clock::GetNow);

        IntervalTimer(const s3d::Duration& time, bool startImmediately = false, Clock_t timeGetter = Clock::GetNow);

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

        /// <summary>
        /// タイマー終了に
        /// </summary>
        /// <returns></returns>
        bool toEnd() const;
    };
}