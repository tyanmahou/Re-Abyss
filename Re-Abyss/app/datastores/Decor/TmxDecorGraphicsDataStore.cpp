#include "TmxDecorGraphicsDataStore.hpp"

namespace abyss
{
    s3d::Array<DecorGraphicsEntity> TmxDecorGraphicsDataStore::select() const
    {
        s3d::Array<DecorGraphicsEntity> ret;
        for (const auto& tile : m_tmx.getTiles()) {
            DecorGraphicsEntity entity{
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
