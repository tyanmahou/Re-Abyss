#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/Shot/Motion.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate;

        bool m_isDamaging = false;
        double m_time = 0;
        Motion m_motion = Motion::Wait;
    public:
        ShotVM();
        ShotVM& setTime(double m_time);

        ShotVM& setPos(const s3d::Vec2& pos);
        ShotVM& setRotate(double rotate);

        ShotVM& setIsDamaging(bool isDamaging);

        ShotVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        void draw() const;
    private:
        void drawBase(double t) const;
        void drawWait() const;
        void drawFiringed() const;
    };
}