#include "LightUtil.hpp"
#include <Siv3D.hpp>

namespace abyss::LightUtil
{
    void DrawCircleLight(const s3d::Vec2& pos, double range, double brightness, double time)
    {
        const double sin0_1 = s3d::Periodic::Sine0_1(2.0s, time);
        const double alpha = s3d::Saturate(brightness * (0.9 + sin0_1 * 0.1));
        const double r = range / 2.0 + 1 * sin0_1;
        const double maxAlphaR = r / 4.0f;
        Circle(pos, maxAlphaR)
            .drawShadow(Vec2::Zero(), r - maxAlphaR, maxAlphaR, ColorF(1.0, alpha));

    }
}
