#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

#include <abyss/types/Forward.hpp>
namespace abyss
{
    class CaptainTakoShotVM
    {
        TexturePacker m_texture;
        Forward m_forward;
        s3d::Vec2 m_pos;
    public:
        CaptainTakoShotVM();
        CaptainTakoShotVM& setForward(const Forward& forward);
        CaptainTakoShotVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}