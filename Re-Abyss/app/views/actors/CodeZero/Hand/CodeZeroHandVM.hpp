#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class CodeZeroHandVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;
        double  m_rotate;
    public:
        CodeZeroHandVM(Forward forward);
        CodeZeroHandVM& setPos(const s3d::Vec2& pos);
        CodeZeroHandVM& setRotate(double rotate);

        void draw(const s3d::Color& color = Palette::White) const;
        void drawAttackWait();
    };
}