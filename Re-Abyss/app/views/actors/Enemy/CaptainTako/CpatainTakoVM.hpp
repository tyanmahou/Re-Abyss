#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>

namespace abyss::Actor::CaptainTako
{
    class CaptainTakoVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        bool m_isDamaging = false;

        double m_time = 0;
    public:
        CaptainTakoVM();
        CaptainTakoVM& setTime(double time);
        CaptainTakoVM& setForward(const Forward& forward);
        CaptainTakoVM& setPos(const s3d::Vec2& pos);

        CaptainTakoVM& setIsDamaging(bool isDamaging);

        void drawWait() const;
        void drawCharge(double chargeTime) const;
    };
}