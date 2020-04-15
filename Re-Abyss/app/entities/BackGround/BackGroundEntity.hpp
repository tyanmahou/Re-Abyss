#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

namespace abyss
{
    struct BackGroundEntity
    {
        s3d::uint32 id;

        s3d::String name;
        s3d::FilePath filePath;
        s3d::Vec2 offset;
        s3d::Vector2D<bool> loop;
        s3d::Vec2 rate;
    };
}