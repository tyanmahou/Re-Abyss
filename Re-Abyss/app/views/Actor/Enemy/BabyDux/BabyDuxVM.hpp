#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/BabyDux/Motion.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    class BabyDuxVM
    {
    public:
        BabyDuxVM();
        BabyDuxVM& setPos(const s3d::Vec2& pos);
        BabyDuxVM& setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR);
        BabyDuxVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
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

        void drawEye() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        s3d::Vec2 m_eyePosL{};
        s3d::Vec2 m_eyePosR{};

        Forward m_forward = Forward::Left;
        double m_time = 0;
        double m_animTime = 0;
        Motion m_motion = Motion::Wait;

        s3d::ColorF m_colorMul;
    };
}
