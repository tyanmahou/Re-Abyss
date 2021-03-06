#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class LaunSharkVM
    {
        TexturePacker m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;

        bool m_isDamaging = false;
        double m_time = 0;
    public:
        LaunSharkVM();
        LaunSharkVM& setTime(double time);
        LaunSharkVM& setForward(const Forward& forward);
        LaunSharkVM& setPos(const s3d::Vec2& pos);

        LaunSharkVM& setIsDamaging(bool isDamaging);

        void drawSwim() const;
        void drawAttack() const;
        void drawLauncher(double launcherTime = 1.0) const;
    };
}