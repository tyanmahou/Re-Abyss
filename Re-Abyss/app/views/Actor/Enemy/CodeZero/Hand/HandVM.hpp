#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/Motion.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;
        double  m_rotate;
        double m_time = 0;
        Motion m_motion = Motion::Wait;
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
        void draw() const;
    private:
        void drawBase(const s3d::Color& color = Palette::White) const;
        void drawAttackWait() const;
    };
}