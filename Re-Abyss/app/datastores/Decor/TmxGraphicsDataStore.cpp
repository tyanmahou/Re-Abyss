#include "TmxGraphicsDataStore.hpp"

namespace abyss::Decor
{
    s3d::Array<GraphicsEntity> TmxGraphicsDataStore::select() const
    {
        s3d::Array<GraphicsEntity> ret;
        for (const auto& [firstGId, tileSet] : m_tmx.getTileSets()) {
            for (const auto& tile : tileSet.getTiles()) {
                GraphicsEntity entity{
                    .gId = tile.tileId + firstGId,
                    .firstGId = firstGId,
                    .filePath = tile.image,
                    .offset = tile.offset,
                    .size = tile.size
                };
                ret.push_back(entity);
            }
        }

        return ret;
    }
}
