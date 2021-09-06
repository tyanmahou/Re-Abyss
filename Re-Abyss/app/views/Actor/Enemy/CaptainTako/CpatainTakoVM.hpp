#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/Motion.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class CaptainTakoVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        bool m_isDamaging = false;

        double m_time = 0;
        double m_chargeRate = 0;
        Motion m_motion = Motion::Wait;
    public:
        CaptainTakoVM();
        CaptainTakoVM& setTime(double time);
        CaptainTakoVM& setForward(const Forward& forward);
        CaptainTakoVM& setPos(const s3d::Vec2& pos);

        CaptainTakoVM& setIsDamaging(bool isDamaging);
        CaptainTakoVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }
        CaptainTakoVM& setChargeRate(double chargeRate)
        {
            m_chargeRate = chargeRate;
            return *this;
        }
        void draw() const;
    private:
        void drawWait() const;
        void drawCharge() const;
    };
}