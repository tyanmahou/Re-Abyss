#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/Motion.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class LaunSharkVM
    {
    public:
        LaunSharkVM();
        LaunSharkVM& setTime(double time);
        LaunSharkVM& setForward(const Forward& forward);
        LaunSharkVM& setPos(const s3d::Vec2& pos);

        LaunSharkVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }

        LaunSharkVM& setAnimeTime(double time)
        {
            m_animeTime = time;
            return *this;
        }
        LaunSharkVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawSwim() const;
        void drawAttack() const;
        void drawLauncher(double launcherTime = 1.0) const;
    private:
        TexturePacker m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        double m_time = 0;
        Motion m_motion = Motion::Attack;
        double m_animeTime = 0;

        s3d::ColorF m_colorMul;
    };
}