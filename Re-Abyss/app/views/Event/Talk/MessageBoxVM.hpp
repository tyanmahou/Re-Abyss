#pragma once
#include <Siv3D/TexturedQuad.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Event::Talk
{
    class MessageBoxVM
    {
        s3d::Texture m_faceIcon;
        s3d::Texture m_boxTexture;
        s3d::Optional<s3d::String> m_name;
        bool m_isLeft = true;

        s3d::Vec2 m_pos;
    public:
        MessageBoxVM();
        MessageBoxVM& setPos(const s3d::Vec2& pos);
        MessageBoxVM& setName(const s3d::Optional<s3d::String>& name);
        MessageBoxVM& setIsLeft(bool isLeft);
        MessageBoxVM& setFaceIcon(const s3d::Texture& face);
        void draw() const;
    };
}