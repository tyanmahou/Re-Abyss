#include <abyss/views/Actor/Player/MotionUtil.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    s3d::int32 MotionUtil::LadderAtkPage(const PlayerVM* view)
    {
        return static_cast<int32>(s3d::Abs(s3d::Floor(view->m_pos.y / 16))) % 2;
    }
    s3d::RectF MotionUtil::LadderAtkRect(const PlayerVM* view)
    {
        auto page = LadderAtkPage(view);
        bool isRight = view->m_forward == Forward::Right;
        return {
            { isRight ? 70 : 0, 80 * page }, { 70, 80 }
        };
    }
    s3d::Optional<s3d::Vec2> MotionUtil::AtkHandPos(const PlayerVM* view)
    {
        switch (view->m_motion)
        {
        case Motion::Stay:
            return s3d::Vec2{ 23 * view->m_forward, -2 };
        case Motion::Float:
            return s3d::Vec2{ 26 * view->m_forward, -4 };
        case Motion::Run:
            return s3d::Vec2{ 30 * view->m_forward, -3 };
        case Motion::Swim:
            return s3d::Vec2{ 30 * view->m_forward, -3 };
        case Motion::Dive:
            return s3d::Vec2{ view->m_forward == Forward::Right ? 22 : -21, -3 };
        case Motion::Damage:
            return s3d::none;
        case Motion::Dead:
            return s3d::none;
        case Motion::Ladder:
        {
            auto page = LadderAtkPage(view);
            bool isRight = view->m_forward == Forward::Right;
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
            return s3d::Vec2{ view->m_forward == Forward::Right ? 17 : -22, -3 };
        }
        case Motion::Door:
            break;
        default:
            break;
        }
        return s3d::none;
    }
}
