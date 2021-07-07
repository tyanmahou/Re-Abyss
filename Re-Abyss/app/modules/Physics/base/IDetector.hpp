#pragma once
#include <abyss/types/CShape.hpp>
#include "TerrainData.hpp"

namespace abyss::Physics
{
    class IDetector
    {
    public:
        virtual ~IDetector() = default;

        virtual s3d::uint64 id() const = 0;

        virtual bool isActive() const = 0;
        virtual const CShape& getShape() const = 0;
        virtual const void onCollision(const TerrainData&) = 0;
    };
}