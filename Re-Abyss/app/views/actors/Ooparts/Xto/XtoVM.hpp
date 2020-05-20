#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss::Xto
{
    class XtoVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
        Forward m_forward;
    public:
        XtoVM();

        XtoVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        XtoVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        void draw() const;
    };
}