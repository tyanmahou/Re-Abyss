#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class SchieldVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Forward m_forward;

        bool m_isDamaging = false;
    public:
        SchieldVM();
        SchieldVM& setPos(const s3d::Vec2& pos);
        SchieldVM& setForward(const Forward& forward);

        SchieldVM& setIsDamaging(bool isDamaging);

        void drawWait() const;
        void drawToWait(double t)const;
        void drawAttackPlus() const;
        void drawToAttackPlus(double t)const;
        void drawAttackCross() const;
        void drawToAttackCross(double t)const;
    };
}