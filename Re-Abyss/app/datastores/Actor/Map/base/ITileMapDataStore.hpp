#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/utils/Chunk/Chunk.hpp>
#include <abyss/entities/Actor/Map/MapEntity.hpp>

namespace abyss::Actor::Map
{
    class ITileMapDataStore
    {
    public:
        virtual ~ITileMapDataStore() = default;

        virtual s3d::Vec2 getTileSize() const = 0;
        virtual s3d::Array<ChunkGrid<MapEntity>> selectGrid() const = 0;
    };
}