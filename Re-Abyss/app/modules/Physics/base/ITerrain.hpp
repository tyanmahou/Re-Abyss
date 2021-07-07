#pragma once
#include "TerrainData.hpp"

namespace abyss::Physics
{
    class ITerrain
    {
    public:
        virtual ~ITerrain() = default;

        virtual s3d::uint64 id() const = 0;

        virtual bool isActive() const = 0;
        virtual const TerrainData& getData() const = 0;
    };
}