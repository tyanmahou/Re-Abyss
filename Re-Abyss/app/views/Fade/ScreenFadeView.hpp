#pragma once
#include <abyss/views/Fade/FadeViewBase.hpp>

namespace abyss::Fade
{
    class ScreenFadeView final : public FadeViewBase
    {
    public:
        void draw(double t, const s3d::RectF& rect) const;
    };
}
