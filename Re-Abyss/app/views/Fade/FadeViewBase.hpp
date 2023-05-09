#pragma once
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Fade
{
    class FadeViewBase
    {
    public:
        void setFadeColor(const s3d::ColorF& color)
        {
            m_fadeColor = color;
        }
    protected:
        bool fadeTimeAdjust(double& t, double factor = 0.75) const;
    protected:

        s3d::ColorF m_fadeColor{ ColorDef::DefaultFadeColor };
    };
}
