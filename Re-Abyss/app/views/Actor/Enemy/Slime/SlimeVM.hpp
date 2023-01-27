#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/values/Forward.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Actor/Enemy/Slime/Motion.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeVM
    {
    public:
        SlimeVM(Resource::Assets* asset = Resource::Assets::Main());
        SlimeVM& setTime(double time);
        SlimeVM& setForward(const Forward& forward);
        SlimeVM& setPos(const s3d::Vec2& pos);
        SlimeVM& setVelocity(const s3d::Vec2& velocity);

        SlimeVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        SlimeVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawWalk() const;
        void drawJump() const;
    private:

        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

        double m_time;

        Motion m_motion = Motion::Walk;
        s3d::ColorF m_colorMul{1, 1};
    };
}