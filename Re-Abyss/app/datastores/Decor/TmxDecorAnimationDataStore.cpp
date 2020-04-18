#include "TmxDecorAnimationDataStore.hpp"
namespace abyss
{
    s3d::Array<DecorAnimationEntity> TmxDecorAnimationDataStore::select() const
    {
        s3d::Array<DecorAnimationEntity> ret;
        s3d::uint32 slot = 0;
        s3d::uint32 prevGId = 0;
        for (auto&& frame : m_tmx.getAnimationFrames()) {
            if (prevGId != frame.from) {
                slot = 0;
            } else {
                ++slot;
            }
            prevGId = frame.from;
            DecorAnimationEntity entity{
                .fromGId = frame.from,
                .slot = slot,
                .toGId = frame.to,
                .timeMilliSec = static_cast<double>(frame.duration)
            };

            ret.push_back(entity);
        }
        return ret;
    }

}
