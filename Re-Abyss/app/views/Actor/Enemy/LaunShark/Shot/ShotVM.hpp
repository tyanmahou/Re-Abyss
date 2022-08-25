#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/Shot/Motion.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class ShotVM
    {
    public:
        ShotVM();
        ShotVM& setTime(double m_time);

        ShotVM& setPos(const s3d::Vec2& pos);
        ShotVM& setRotate(double rotate);

        ShotVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        ShotVM& setColorMul(const s3d::ColorF color);

        void draw() const;
    private:
        void drawBase(double t) const;
        void drawWait() const;
        void drawFiringed() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate;

        double m_time = 0;
        Motion m_motion = Motion::Wait;
        s3d::ColorF m_colorMul;
    };
}