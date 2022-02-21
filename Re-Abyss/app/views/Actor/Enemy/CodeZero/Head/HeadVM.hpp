#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Look.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class HeadVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Look m_look;
        bool m_isDamaging = false;
        double m_time = 0;
    public:
        HeadVM();
        HeadVM& setTime(double time);
        HeadVM& setPos(const s3d::Vec2& pos);
        HeadVM& setLook(const Look& look);
        HeadVM& setIsDamaging(bool isDamaging);
        void draw() const;
    };
}