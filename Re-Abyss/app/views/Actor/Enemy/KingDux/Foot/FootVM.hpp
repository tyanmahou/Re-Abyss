#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::KingDux::Foot
{
    class FootVM
    {
    public:
        FootVM();
        FootVM& setTime(double time);
        FootVM& setPos(const s3d::Vec2& pos);
        FootVM& setRotate(double rotate);

        FootVM& setIsDamaging(bool isDamaging);
        FootVM& setInvincibleColor(const s3d::ColorF color);
        FootVM& setIsFlip(bool isFlip);
        FootVM& setDamageTime(double damageTime);
        void draw() const;
    private:

        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0;
        bool m_isDamaging = false;
        s3d::ColorF m_invincibleColor;
        bool m_isFlip = false;
        double m_time = 0;
        double m_damageTime = 0;
    };
}
