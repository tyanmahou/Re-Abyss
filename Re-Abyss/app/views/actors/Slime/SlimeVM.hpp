#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>

namespace abyss
{
    class SlimeVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

        bool m_isDamaging = false;
    public:
        SlimeVM();
        SlimeVM& setForward(const Forward& forward);
        SlimeVM& setPos(const s3d::Vec2& pos);
        SlimeVM& setVelocity(const s3d::Vec2& velocity);

        SlimeVM& setIsDamaging(bool isDamaging);

        void drawWalk() const;
        void drawJump() const;
    };
}