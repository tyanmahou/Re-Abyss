#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class SlimeVM
    {
        s3d::Texture m_texture;

        Forward m_forward;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

    public:
        SlimeVM();
        void bind(const SlimeActor& actor);
        void drawWalk() const;
        void drawJump() const;
    };
}