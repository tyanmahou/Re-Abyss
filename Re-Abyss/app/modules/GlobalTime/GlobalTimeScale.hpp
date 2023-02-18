#pragma once

namespace abyss
{
    class GlobalTimeScale
    {
    public:
        GlobalTimeScale() = default;

        GlobalTimeScale& setScale(double scale)
        {
            m_scale = scale;
            return *this;
        }

        double getScale() const
        {
            return m_scale;
        }
    private:
        double m_scale = 1.0;
    };
}
