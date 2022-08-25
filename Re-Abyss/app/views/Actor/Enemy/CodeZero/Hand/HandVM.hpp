#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/entities/Forward.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/Motion.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandVM
    {
    public:
        HandVM(Forward forward);
        HandVM& setTime(double time);
        HandVM& setPos(const s3d::Vec2& pos);
        HandVM& setRotate(double rotate);
        HandVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        HandVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawBase(const s3d::Color& color = s3d::Palette::White) const;
        void drawAttackWait() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;
        double  m_rotate;
        double m_time = 0;
        Motion m_motion = Motion::Wait;
        s3d::ColorF m_colorMul;
    };
}