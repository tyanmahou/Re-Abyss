#pragma once
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::TimeLite
{
    /// <summary>
    /// インターバルタイマー
    /// </summary>
    class IntervalTimer
    {
    public:
        IntervalTimer(double time = 0, s3d::int32 maxCount = -1) :
            m_total(time),
            m_maxCount(maxCount)
        {}
        IntervalTimer(s3d::Duration duration, s3d::int32 maxCount = -1) :
            IntervalTimer(duration.count(), maxCount)
        {}
        Coro::Generator<s3d::int32> update(double dt)
        {
            if (isMaxCount()) {
                co_return;
            }

            m_current += dt;
            while (m_current >= m_total && !isMaxCount()) {
                m_current -= m_total;
                if (m_count == std::numeric_limits<s3d::int32>::max()) {
                    m_count = 0;
                } else {
                    ++m_count;
                }
                co_yield m_count;
            }
            co_return;
        }
        bool isMaxCount() const
        {
            return m_maxCount >= 0 && m_count >= m_maxCount;
        }
    private:
        double m_current = 0;
        double m_total = 0;
        s3d::int32 m_count = 0;
        s3d::int32 m_maxCount = 0;
    };
}