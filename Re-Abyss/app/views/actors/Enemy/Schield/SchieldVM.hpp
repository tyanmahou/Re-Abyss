#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class SchieldVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;

        bool m_isDamaging = false;
        double m_time = 0;
    public:
        SchieldVM();
        SchieldVM& setTime(double time);
        SchieldVM& setPos(const s3d::Vec2& pos);
        SchieldVM& setForward(const Forward& forward);

        SchieldVM& setIsDamaging(bool isDamaging);

        void drawWait() const;
        void drawToWait(double t)const;
        void drawAttackPlus() const;
        void drawToAttackPlus(double t)const;
        void drawAttackCross() const;
        void drawToAttackCross(double t)const;
    };
}