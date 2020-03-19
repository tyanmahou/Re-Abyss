#pragma once
#include <abyss/types/Forward.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss::Slime
{
    class SlimeVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

    public:
        SlimeVM();

        void drawWalk() const;
        void drawJump() const;
    };
}