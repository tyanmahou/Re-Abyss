#include <abyss/views/util/Anim/AnimUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    s3d::int32 AnimUtil::FrameFromRate(double rate, s3d::int32 frameSize)
    {
        int32 frame = static_cast<int32>(rate * frameSize);
        if (frame == frameSize) {
            frame = frameSize - 1;
        }
        return frame;
    }

    s3d::int32 AnimUtil::FrameFromMap(double rate, const s3d::Array<s3d::int32>& map)
    {
        return map[FrameFromRate(rate, static_cast<int32>(map.size()))];
    }
    s3d::int32 AnimUtil::FrameFromSaw(double period, double time, s3d::int32 frameSize)
    {
        return FrameFromRate(Periodic::Sawtooth0_1(period, time), frameSize);
    }
    s3d::int32 AnimUtil::FrameFromTriangle(double period, double time, s3d::int32 frameSize)
    {
        return FrameFromRate(Periodic::Triangle0_1(period, time), frameSize);
    }

}
