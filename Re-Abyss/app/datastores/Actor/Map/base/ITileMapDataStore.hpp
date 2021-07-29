#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/Grid.hpp>

namespace abyss::Actor::Map
{
    class ITileMapDataStore
    {
    public:
        virtual ~ITileMapDataStore() = default;

        virtual s3d::Vec2 getTileSize() const = 0;
        virtual s3d::Array<s3d::Grid<s3d::uint32>> selectRawGrid() const = 0;
    };
}