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
        IntervalTimer(double time = 1, s3d::int32 maxCount = -1) :
            m_total(time),
            m_maxCount(maxCount)
        {}
        IntervalTimer(s3d::Duration duration, s3d::int32 maxCount = -1) :
            IntervalTimer(duration.count(), maxCount)
        {}
        void setInitTimeOffset(double offset)
        {
            if (!isValid()) {
                return;
            }
            m_current = s3d::Fmod(offset, m_total);
        }
        [[nodiscard]] Coro::Generator<double> update(double dt)
        {
            if (!isValid()) {
                co_return;
            }
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
                co_yield m_current;
            }
            co_return;
        }
        void update(double dt, std::function<void()> callback)
        {
            for ([[maybe_unused]] double carryOver : this->update(dt)) {
                callback();
            }
        }
        void update(double dt, std::function<void(double)> callback)
        {
            for (double carryOver : this->update(dt)) {
                callback(carryOver);
            }
        }
        bool isMaxCount() const
        {
            return m_maxCount >= 0 && m_count >= m_maxCount;
        }
        bool isValid() const
        {
            return m_total > 0;
        }
    private:
        double m_current = 0;
        double m_total = 0;
        s3d::int32 m_count = 0;
        s3d::int32 m_maxCount = 0;
    };
}