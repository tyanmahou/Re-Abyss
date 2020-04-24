#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::CodeZero::Head
{
    class HeadVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;

        bool m_isDamaging = false;
    public:
        HeadVM();
        HeadVM& setPos(const s3d::Vec2& pos);
        HeadVM& setForward(Forward forward);
        HeadVM& setIsDamaging(bool isDamaging);
        void draw() const;
    };
}