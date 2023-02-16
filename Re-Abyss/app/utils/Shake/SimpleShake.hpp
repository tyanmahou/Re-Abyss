#pragma once
#include <abyss/values/Fps.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Shake
{
    /// <summary>
    /// ゆれ実装
    /// </summary>
    class SimpleShake
    {
    public:
        SimpleShake();

        void update(double dt, double erpRate = 0.99);

        void request(double maxOffset, double timeSec);
        void stop();

        const s3d::Vec2& getShakeOffset() const
        {
            return m_offset;
        }

        bool isShakeing() const;
        bool isEnd() const;
    private:
        double m_maxOffset = 0;
        double m_timeSec = 0.0;
        double m_elapsedSec = 0.0;

        double m_nextTargetTimeSec = 0.0;
        Vec2 m_offsetTarget{};

        s3d::Vec2 m_offset{};

        bool m_isStop = false;
    };
}
