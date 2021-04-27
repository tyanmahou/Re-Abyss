#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Decor
{
    struct GraphicsEntity
    {
        s3d::uint32 gId;
        s3d::uint32 firstGId;
        s3d::String filePath;
        s3d::Vec2 offset;
        s3d::Vec2 size;
    };
}