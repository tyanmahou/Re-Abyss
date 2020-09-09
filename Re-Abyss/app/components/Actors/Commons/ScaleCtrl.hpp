#pragma once
#include <Siv3D/Optional.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// Scale制御
    /// </summary>
    class ScaleCtrl : public IComponent
    {
        double m_scale = 1.0;

        s3d::Optional<double> m_minScale;
        s3d::Optional<double> m_maxScale;
        double m_rate = 0.0;
    public:
        ScaleCtrl() = default;
        ScaleCtrl(double initScale);

        double get()const
        {
            return m_scale;
        }
        ScaleCtrl& set(double value)
        {
            m_scale = value;
            return *this;
        }
        ScaleCtrl& setRate(double rate)
        {
            m_rate = rate;
            return *this;
        }

        ScaleCtrl& setMax(double max)
        {
            m_maxScale = max;
            return *this;
        }
        ScaleCtrl& setMin(double min)
        {
            m_minScale = min;
            return *this;
        }
        ScaleCtrl& setTo(double scale, double timeSec);
        ScaleCtrl& setTo(double init, double to, double timeSec);

        void update(double dt);
    };
}