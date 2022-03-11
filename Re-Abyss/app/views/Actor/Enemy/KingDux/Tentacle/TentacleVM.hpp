#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class TentacleVM
    {
    public:
        TentacleVM();

        TentacleVM& setTime(double time);
        TentacleVM& setPos(const s3d::Vec2& pos);
        TentacleVM& setRotate(double rotate);
        TentacleVM& setIsDamaging(bool isDamaging);
        TentacleVM& setInvincibleColor(const s3d::ColorF color);
        void draw() const;
    private:

        s3d::Texture m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0;
        bool m_isDamaging = false;
        s3d::ColorF m_invincibleColor;
        double m_time = 0;
    };
}