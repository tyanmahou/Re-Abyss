#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>
namespace abyss
{
    class CaptainTakoShotVM
    {
        s3d::Texture m_texture;
        Forward m_forward;
        s3d::Vec2 m_pos;
    public:
        CaptainTakoShotVM();
        CaptainTakoShotVM& setForward(const Forward& forward);
        CaptainTakoShotVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}