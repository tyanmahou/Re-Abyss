#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::LightUtil
{
    /// <summary>
    /// サークルライト
    /// </summary>
    void DrawCircleLight(const s3d::Vec2& pos, double range, double brightness, double time);
}