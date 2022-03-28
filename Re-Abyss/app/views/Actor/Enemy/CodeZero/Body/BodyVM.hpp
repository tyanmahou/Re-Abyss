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

        void draw() const;
    private:

        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        s3d::ColorF m_colorMul;
    };
}