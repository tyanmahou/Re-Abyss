#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/entities/Forward.hpp>
#include <abyss/views/Actor/Enemy/RollingTako/Motion.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class RollingTakoVM
    {
    public:
        RollingTakoVM();
        RollingTakoVM& setTime(double time);
        RollingTakoVM& setForward(const Forward& forward);
        RollingTakoVM& setPos(const s3d::Vec2& pos);

        RollingTakoVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        RollingTakoVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawWait() const;
        void drawRun() const;
    private:
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        double m_time;
        Motion m_motion = Motion::Wait;
        s3d::ColorF m_colorMul;
    };
}