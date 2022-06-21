#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Layout::Window::detail
{
    /// <summary>
    /// 定数
    /// </summary>
    class Constants
    {
    public:
        static constexpr double Margin = 5.0;

        static constexpr double ScrollMargin = 15.0;

        static constexpr double ScrollBarSize = 20.0;

        static constexpr s3d::Vec2 WinMinSize{
            ScrollMargin * 3.0 + Margin + ScrollBarSize,
            ScrollMargin * 3.0 + Margin + ScrollBarSize
        };
    };
}
