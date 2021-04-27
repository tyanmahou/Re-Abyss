#pragma once
#include <Siv3D/Grid.hpp>

namespace abyss
{
    class ITileMapDataStore
    {
    public:
        virtual ~ITileMapDataStore() = default;

        virtual s3d::Vec2 getTileSize() const = 0;
        virtual s3d::Grid<s3d::uint32> selectRawGrid() const = 0;
    };
}