#pragma once
#include <Siv3D/Duration.hpp>

namespace abyss::TimeLite
{
    class Timer
    {
    public:
        Timer(double time = 0):
            m_total(time)
        {}

        double update(double dt)
        {
            m_current += dt;
            if (m_current >= m_total) {
                auto tmp = m_current;
                m_current = m_total;
                return tmp - m_total;
            }
            return 0.0;
        }

        bool isEnd() const
        {
            return m_current >= m_total;
        }
        double rate() const
        {
            if (m_total == 0) {
                return 1.0;
            }
            return m_current / m_total;
        }
        double invRate() const
        {
            return 1.0 - rate();
        }
        void toEnd()
        {
            m_current = m_total;
        }

        double current() const
        {
            return m_current;
        }

        double rest() const
        {
            return m_total - m_current;
        }

        void reset()
        {
            m_current = 0;
        }
        void reset(double total)
        {
            m_current = 0;
            m_total = total;
        }
        bool isRunning() const
        {
            return m_current > 0;
        }
    private:
        double m_current = 0;
        double m_total = 0;
    };
}