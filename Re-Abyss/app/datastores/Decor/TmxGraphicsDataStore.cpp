#include "TmxGraphicsDataStore.hpp"

namespace abyss::decor
{
    s3d::Array<GraphicsEntity> TmxGraphicsDataStore::select() const
    {
        s3d::Array<GraphicsEntity> ret;
        for (const auto& tile : m_tmx.getTiles()) {
            GraphicsEntity entity{
                .gId = tile.gId,
                .filePath = tile.image,
                .offset = tile.offset,
                .size = tile.size
            };
            ret.push_back(entity);
        }

        return ret;
    }
}
