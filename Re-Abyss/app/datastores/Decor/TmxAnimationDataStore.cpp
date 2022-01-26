#include <abyss/datastores/Decor/TmxAnimationDataStore.hpp>

namespace abyss::Decor
{
    s3d::Array<AnimationEntity> TmxAnimationDataStore::select() const
    {
        s3d::Array<AnimationEntity> ret;
        s3d::uint32 slot = 0;
        s3d::uint32 prevGId = 0;
        for (const auto& [firstGId, tileSet] : m_tmx.getTileSets()) {
            for (const auto& tile : tileSet.getTiles()) {
                auto from = tile.tileId + firstGId;
                for (const auto& [to, duration] : tile.animation.getFrames()) {
                    if (prevGId != from) {
                        slot = 0;
                    } else {
                        ++slot;
                    }
                    prevGId = from;
                    AnimationEntity entity{
                        .fromGId = from,
                        .slot = slot,
                        .toGId = to + firstGId,
                        .timeMilliSec = static_cast<double>(duration)
                    };

                    ret.push_back(entity);
                }
            }
        }
        return ret;
    }
}
