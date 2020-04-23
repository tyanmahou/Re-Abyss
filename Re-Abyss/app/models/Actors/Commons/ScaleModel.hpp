#pragma once
#include <Siv3D/Optional.hpp>
namespace abyss
{
    /// <summary>
    /// Scale制御
    /// </summary>
    class ScaleModel
    {
        double m_scale = 1.0;

        s3d::Optional<double> m_minScale;
        s3d::Optional<double> m_maxScale;
        double m_rate = 0.0;
    public:
        ScaleModel() = default;
        ScaleModel(double initScale);

        double get()const
        {
            return m_scale;
        }
        ScaleModel& set(double value)
        {
            m_scale = value;
            return *this;
        }
        ScaleModel& setRate(double rate)
        {
            m_rate = rate;
            return *this;
        }

        ScaleModel& setMax(double max)
        {
            m_maxScale = max;
            return *this;
        }
        ScaleModel& setMin(double min)
        {
            m_minScale = min;
            return *this;
        }
        ScaleModel& setTo(double scale, double timeSec);
        ScaleModel& setTo(double init, double to, double timeSec);

        void update(double dt);
    };
}