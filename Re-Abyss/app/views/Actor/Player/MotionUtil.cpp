#include <abyss/views/Actor/Player/MotionUtil.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;

    int32 GetTimeInt32(double time)
    {
        return static_cast<int32>(time * 60);
    }
}

namespace abyss::Actor::Player
{
    s3d::RectF MotionUtil::StayRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        int32 page = timer % 240 <= 10 ? 1 : 0;
        return { { isRight ? 40 : 0, 80 * page }, { 40, 80 } };
    }
    s3d::RectF MotionUtil::StayAtkRect(const PlayerVM* view)
    {
        bool isRight = view->m_forward.isRight();
        return { { 0, isRight ? 80 : 0 }, { 80, 80 } };
    }
    s3d::RectF MotionUtil::FloatRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        double y = 160;
        if (view->m_velocity.y < -96) {
            y = 0;
        } else if (view->m_velocity.y < -48) {
            y = 80;
        } else {
            y = 80 * (timer / 30 % 2) + 160;
        }
        return { { isRight ? 60 : 0, y }, { 60, 80 } };
    }
    s3d::RectF MotionUtil::FloatAtkRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        double y = 80 * (timer / 30 % 2);
        return { { isRight ? 70 : 0, y }, { 70, 80 } };
    }
    s3d::RectF MotionUtil::RunRect(const PlayerVM* view)
    {
        bool isRight = view->m_forward.isRight();
        int32 x = static_cast<int32>(Periodic::Triangle0_1(1.2s, view->m_time) * 5) * 60;
        return { { x, isRight ? 80 : 0 }, { 60, 80 } };
    }
    s3d::RectF MotionUtil::RunAtkRect(const PlayerVM* view)
    {
        bool isRight = view->m_forward.isRight();
        auto page = static_cast<int32>(Periodic::Triangle0_1(1.2s, view->m_time) * 5);
        if (page == 3) {
            page = 1;
        } else if (page == 4) {
            page = 0;
        }
        int32 x = page * 80;
        return { { x, isRight ? 80 : 0 }, { 80, 80 } };
    }
    s3d::RectF MotionUtil::SwimRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        double y = 0;
        if (view->m_velocity.y < -96) {
            y = 160;
        } else if (view->m_velocity.y < -48) {
            y = 240;
        } else {
            y = 80 * (timer / 30 % 2);
        }
        return { { isRight ? 60 : 0, y }, { 60, 80 } };
    }
    s3d::RectF MotionUtil::SwimAtkRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();
        return { { isRight ? 80 : 0, 80 * (timer / 30 % 2) }, { 80, 80 } };
    }
    s3d::RectF MotionUtil::DiveRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        double y = 80 * (timer / 30 % 2);
        return { { isRight ? 60 : 0, y }, { 60, 80 } };
    }
    s3d::RectF MotionUtil::DiveAtkRect(const PlayerVM* view)
    {
        int32 timer = GetTimeInt32(view->m_time);
        bool isRight = view->m_forward.isRight();

        double y = 80 * (timer / 30 % 2);
        return { { isRight ? 80 : 0, y }, { 80, 80 } };
    }
    s3d::RectF MotionUtil::DamageRect(const PlayerVM* view)
    {
        bool isRight = view->m_forward.isRight();
        return { { isRight ? 60 : 0, 0 }, { 60, 80 } };
    }
    s3d::RectF MotionUtil::DeadRect(const PlayerVM* view, Vec2* outPos)
    {
        bool isRight = view->m_forward.isRight();

        int32 frame = static_cast<int32>(s3d::Math::Lerp(0, 5, s3d::Pow(view->m_animeTime, 1.8)));
        if (frame == 5) {
            frame = 4;
        }
        *outPos = view->m_pos;
        if (frame == 4) {
            outPos->y += 3;
        }

        return { { isRight ? 80 : 0, frame * 80 }, {80, 80} };
    }
    s3d::RectF MotionUtil::LadderRect(const PlayerVM* view)
    {
        return { { 40 * (static_cast<int32>(s3d::Abs(s3d::Floor(view->m_pos.y / 16))) % 2), 0 }, { 40, 80 } };
    }
    s3d::int32 MotionUtil::LadderAtkPage(const PlayerVM* view)
    {
        return static_cast<int32>(s3d::Abs(s3d::Floor(view->m_pos.y / 16))) % 2;
    }
    s3d::RectF MotionUtil::LadderAtkRect(const PlayerVM* view)
    {
        auto page = LadderAtkPage(view);
        bool isRight = view->m_forward.isRight();
        return {
            { isRight ? 70 : 0, 80 * page }, { 70, 80 }
        };
    }
    s3d::RectF MotionUtil::LadderTopRect([[maybe_unused]]const PlayerVM* view)
    {
        return { { 80, 0 }, { 40, 80 } };
    }
    s3d::RectF MotionUtil::LadderTopAtkRect(const PlayerVM* view)
    {
        bool isRight = view->m_forward.isRight();
        return { { isRight ? 70 : 0, 160 }, { 70, 80 } };
    }
    s3d::RectF MotionUtil::DoorRect(const PlayerVM* view)
    {
        return {
            { 40 * static_cast<int32>(Periodic::Sawtooth0_1(1s, view->m_time) * 2), 0 },
            { 40, 80 }
        };
    }
    s3d::Optional<s3d::Vec2> MotionUtil::AtkHandPos(const PlayerVM* view)
    {
        switch (view->m_motion)
        {
        case Motion::Stay:
            return s3d::Vec2{ 23 * view->m_forward.signH(), -2};
        case Motion::Float:
            return s3d::Vec2{ 26 * view->m_forward.signH(), -4 };
        case Motion::Run:
            return s3d::Vec2{ 30 * view->m_forward.signH(), -3 };
        case Motion::Swim:
            return s3d::Vec2{ 30 * view->m_forward.signH(), -3 };
        case Motion::Dive:
            return s3d::Vec2{ view->m_forward.isRight() ? 22 : -21, -3};
        case Motion::Damage:
            return s3d::none;
        case Motion::Dead:
            return s3d::none;
        case Motion::Ladder:
        {
            auto page = LadderAtkPage(view);
            bool isRight = view->m_forward.isRight();
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
            return s3d::Vec2{ view->m_forward.isRight() ? 17 : -22, -3};
        }
        case Motion::Door:
            break;
        default:
            break;
        }
        return s3d::none;
    }
}
