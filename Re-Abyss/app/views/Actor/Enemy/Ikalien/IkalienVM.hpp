#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/views/Actor/Enemy/Ikalien/Motion.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class IkalienVM
    {
        s3d::Texture m_texture;

        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;
        double m_rotate = 0.0;

        bool m_isDamaging = false;
        double m_time = 0;
        Motion m_motion = Motion::Wait;
    public:
        IkalienVM();
        IkalienVM& setTime(double time);
        IkalienVM& setPos(const s3d::Vec2& pos);
        IkalienVM& setVelocity(const s3d::Vec2& velocity);
        IkalienVM& setRotate(double rotate);

        IkalienVM& setIsDamaging(bool isDamaging);
        IkalienVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        void draw() const;
    private:
        void drawWait() const;
        void drawPursuit() const;
        void drawSwim() const;
    };
}