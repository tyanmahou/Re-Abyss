#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/views/Actor/Enemy/Schield/Motion.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class SchieldVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;

        bool m_isDamaging = false;
        double m_time = 0;

        Motion m_motion;
        double m_animeTime = 0;
    public:
        SchieldVM();
        SchieldVM& setTime(double time);
        SchieldVM& setPos(const s3d::Vec2& pos);
        SchieldVM& setForward(const Forward& forward);

        SchieldVM& setIsDamaging(bool isDamaging);

        SchieldVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        SchieldVM& setAnimeTime(double time)
        {
            m_animeTime = time;
            return *this;
        }
        void draw() const;
    private:
        void drawWait() const;
        void drawToWait(double t)const;
        void drawAttackPlus() const;
        void drawToAttackPlus(double t)const;
        void drawAttackCross() const;
        void drawToAttackCross(double t)const;
    };
}