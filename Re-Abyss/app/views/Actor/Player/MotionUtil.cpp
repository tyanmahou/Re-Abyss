#include <abyss/views/Actor/Player/MotionUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    s3d::Optional<s3d::Vec2> MotionUtil::AtkHandPos(Motion motion, Forward forward, const s3d::Vec2& pos)
    {
        switch (motion)
        {
        case Motion::Stay:
            return s3d::Vec2{ 23 * forward, -2 };
        case Motion::Float:
            return s3d::Vec2{ 26 * forward, -4 };
        case Motion::Run:
            return s3d::Vec2{ 30 * forward, -3 };
        case Motion::Swim:
            return s3d::Vec2{ 30 * forward, -3 };
        case Motion::Dive:
            return s3d::Vec2{ forward == Forward::Right ? 22 : -21, -3 };
        case Motion::Damage:
            return s3d::none;
        case Motion::Dead:
            return s3d::none;
        case Motion::Ladder:
        {
            auto page = static_cast<int32>(s3d::Abs(s3d::Floor(pos.y / 16))) % 2;
            bool isRight = forward == Forward::Right;
            double offsetX = 0.0;
            if (page == 0) {
                offsetX = isRight ? 17 : -27;
            } else {
                offsetX = isRight ? 18 : -26;
            }
            return s3d::Vec2{ offsetX, -3 };
        }
        case Motion::LadderTop:
        {
            return s3d::Vec2{ forward == Forward::Right ? 17 : -22, -3 };
        }
        case Motion::Door:
            break;
        default:
            break;
        }
        return s3d::none;
    }
}
