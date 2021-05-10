#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::DistUtil
{
    /// <summary>
    /// 円
    /// </summary>
    void Draw(const s3d::Circle& circle, double innerPower, double outerPower);
    void Draw(const s3d::Circle& circle, double power);

    /// <summary>
    /// 円フレーム
    /// </summary>
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower);

    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double power);

    void DrawFrame(const s3d::Circle& circle, double thickness, double power);
}