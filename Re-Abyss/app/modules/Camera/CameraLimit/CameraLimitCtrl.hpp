#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class CameraLimitCtrl
    {
    public:
        s3d::Vec2 apply(const s3d::Vec2& targetPos) const;
    private:
    };
}