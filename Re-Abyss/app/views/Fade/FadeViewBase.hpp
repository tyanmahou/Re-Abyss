#pragma once
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Fade
{
    class FadeViewBase
    {
    public:
        void setFadeColor(const s3d::Color& color)
        {
            m_fadeColor = color;
        }
    protected:
        bool fadeTimeAdjust(double& t, double factor = 0.75) const;
    protected:

        s3d::Color m_fadeColor{ ColorDef::DefaultFadeColor };
    };
}
