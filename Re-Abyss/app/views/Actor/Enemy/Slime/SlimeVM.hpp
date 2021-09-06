#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Actor/Enemy/Slime/Motion.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

        bool m_isDamaging = false;
        double m_time;

        Motion m_motion = Motion::Walk;
    public:
        SlimeVM(Resource::Assets* asset = Resource::Assets::Main());
        SlimeVM& setTime(double time);
        SlimeVM& setForward(const Forward& forward);
        SlimeVM& setPos(const s3d::Vec2& pos);
        SlimeVM& setVelocity(const s3d::Vec2& velocity);

        SlimeVM& setIsDamaging(bool isDamaging);

        SlimeVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        void draw() const;
    private:
        void drawWalk() const;
        void drawJump() const;
    };
}