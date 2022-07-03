#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/KingDux/BabyDux/Motion.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class BabyDuxVM
    {
    public:
        BabyDuxVM();
        BabyDuxVM& setPos(const s3d::Vec2& pos);

        BabyDuxVM& setTime(double time);
        BabyDuxVM& setAnimTime(double time);

        BabyDuxVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        BabyDuxVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawWait() const;
        void drawCharge() const;
        void drawJump() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_time = 0;
        double m_animTime = 0;
        Motion m_motion = Motion::Wait;

        s3d::ColorF m_colorMul;
    };
}
