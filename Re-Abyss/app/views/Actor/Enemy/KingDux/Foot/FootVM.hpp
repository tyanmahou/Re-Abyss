#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Motion.hpp>

namespace abyss::Actor::Enemy::KingDux::Foot
{
    class FootVM
    {
    public:
        FootVM();
        FootVM& setTime(double time);
        FootVM& setAnimTime(double time);
        FootVM& setPos(const s3d::Vec2& pos);
        FootVM& setRotate(double rotate);

        FootVM& setIsFlip(bool isFlip);
        FootVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        FootVM& setColorMul(const s3d::ColorF color);
        FootVM& setColorAdd(const s3d::ColorF color);
        void draw() const;
    private:

        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0;
        bool m_isFlip = false;
        double m_time = 0;
        double m_animTime = 0;
        Motion m_motion = Motion::Wait;

        s3d::ColorF m_colorMul;
        s3d::ColorF m_colorAdd;
    };
}
