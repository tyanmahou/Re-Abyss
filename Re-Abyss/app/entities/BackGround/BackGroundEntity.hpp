#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>

namespace abyss
{
    struct BackGroundEntity
    {
        s3d::uint32 id;

        s3d::String name;
        s3d::FilePath filePath;
        s3d::Vec2 offset;
        s3d::Vector2D<bool> fix;
        s3d::Vector2D<s3d::Optional<double>> rate;

        BackGroundEntity() = default;
        BackGroundEntity(const BackGroundEntity&other):
            id(other.id),
            name(other.name),
            filePath(other.filePath),
            offset(other.offset),
            fix(other.fix),
            rate(other.rate.x, other.rate.y)
        {}
        BackGroundEntity(BackGroundEntity&& other) noexcept:
            id(other.id),
            name(std::move(other.name)),
            filePath(std::move(other.filePath)),
            offset(other.offset),
            fix(other.fix),
            rate(std::move(other.rate.x), std::move(other.rate.y))
        {}
    };
}