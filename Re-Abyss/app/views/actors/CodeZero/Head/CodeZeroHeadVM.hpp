#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class CodeZeroHeadVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;

        bool m_isDamaging = false;
    public:
        CodeZeroHeadVM();
        CodeZeroHeadVM& setPos(const s3d::Vec2& pos);
        CodeZeroHeadVM& setForward(Forward forward);
        CodeZeroHeadVM& setIsDamaging(bool isDamaging);
        void draw() const;
    };
}