#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::DistUtil
{
    /// <summary>
    /// 円フレーム
    /// </summary>
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower);

    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double power);

    void DrawFrame(const s3d::Circle& circle, double thickness, double power);
}