#include "TmxAnimationDataStore.hpp"

namespace abyss::decor
{
    s3d::Array<AnimationEntity> TmxAnimationDataStore::select() const
    {
        s3d::Array<AnimationEntity> ret;
        s3d::uint32 slot = 0;
        s3d::uint32 prevGId = 0;
        for (auto&& frame : m_tmx.getAnimationFrames()) {
            if (prevGId != frame.from) {
                slot = 0;
            } else {
                ++slot;
            }
            prevGId = frame.from;
            AnimationEntity entity{
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
