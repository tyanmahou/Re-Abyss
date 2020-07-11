#pragma once

namespace abyss
{
    class GlobalTimeScaleModel
    {
        double m_scale = 1.0;
    public:
        GlobalTimeScaleModel() = default;

        GlobalTimeScaleModel& setScale(double scale)
        {
            m_scale = scale;
            return *this;
        }

        double getScale() const
        {
            return m_scale;
        }
    };
}