#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/utils/Chunk/Chunk.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>

namespace abyss::Actor::Land
{
    class ITileMapDataStore
    {
    public:
        virtual ~ITileMapDataStore() = default;

        virtual s3d::Vec2 getTileSize() const = 0;
        virtual s3d::Array<ChunkGrid<LandEntity>> selectGrid() const = 0;
    };
}
