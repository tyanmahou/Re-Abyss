#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Motion.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class KingDuxVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        s3d::Vec2 m_eyePosL{0, 0};
        s3d::Vec2 m_eyePosR{0, 0};
        bool m_isDamaging = false;
        double m_time = 0;
        Motion m_motion = Motion::Wait;
    public:
        KingDuxVM();
        KingDuxVM& setTime(double time);
        KingDuxVM& setPos(const s3d::Vec2& pos);
        KingDuxVM& setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR);

        KingDuxVM& setIsDamaging(bool isDamaging);
        KingDuxVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        void draw() const;
    };
}