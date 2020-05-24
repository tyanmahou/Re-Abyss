#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>

namespace abyss::RollingTako
{
    class RollingTakoVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        bool m_isDamaging = false;
        double m_time;
    public:
        RollingTakoVM();
        RollingTakoVM& setTime(double time);
        RollingTakoVM& setForward(const Forward& forward);
        RollingTakoVM& setPos(const s3d::Vec2& pos);

        RollingTakoVM& setIsDamaging(bool isDamaging);

        void drawWait() const;
        void drawRun() const;
    };
}