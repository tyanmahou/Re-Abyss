#pragma once
#include <Siv3D/RectF.hpp>

namespace abyss::Layout::Window::detail
{
    struct WindowParam
    {
        SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

        union {
            struct {
                s3d::Vec2 pos;
                s3d::Vec2 size;
            };
            struct {
                s3d::RectF region;
            };
        };

        SIV3D_DISABLE_MSVC_WARNINGS_POP()

        s3d::Vec2 scenePos;
        s3d::Vec2 sceneSize;

        s3d::Optional<ColorF> backGroundColor;
        s3d::Optional<ColorF> frameColor;
        s3d::ColorF scrollBarColor;
        s3d::ColorF scrollGripColor;

        bool canResize;
        bool isResizeClampSceneSize;
        bool canMove;
        bool canScroll;
    };
}
