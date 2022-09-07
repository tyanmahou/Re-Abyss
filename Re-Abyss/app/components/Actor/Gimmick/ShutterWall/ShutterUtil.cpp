#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    s3d::RectF ShutterUtil::Region(const s3d::Vec2& pos, double shutterRate)
    {
        const Vec2& baseSize = Param::BaseSize;
        return {
            pos - baseSize / 2,
            baseSize.x,
            baseSize.y * shutterRate
        };
    }
    s3d::Vec2 ShutterUtil::CenterPosFromTl(const s3d::Vec2& pos)
    {
        return Region(pos).center();
    }
}
