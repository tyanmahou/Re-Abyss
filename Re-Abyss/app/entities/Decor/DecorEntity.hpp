#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    enum class DecorGroup
    {
        Back,
        Front,
    };

    struct DecorEntity
    {
        s3d::uint32 id;
        DecorGroup group;
        s3d::uint32 gId;
        s3d::Vec2 pos;
        s3d::Vec2 size;
        double rotation;
        bool isMirrored = false;
        bool isFliped = false;
    };
}