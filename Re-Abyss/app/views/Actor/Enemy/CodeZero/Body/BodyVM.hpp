#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::CodeZero::Body
{
    class BodyVM
    {
    public:
        BodyVM();
        BodyVM& setPos(const s3d::Vec2& pos);
        BodyVM& setColorMul(const s3d::ColorF color);

        BodyVM& setWingLPos(const s3d::Vec2& pos);
        BodyVM& setWingRPos(const s3d::Vec2& pos);

        void draw() const;
    private:

        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        s3d::Vec2 m_wingLPos;
        s3d::Vec2 m_wingRPos;
        s3d::ColorF m_colorMul;
    };
}
