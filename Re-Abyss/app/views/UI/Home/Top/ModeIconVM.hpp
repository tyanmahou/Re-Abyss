#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::Home::Top
{
    class ModeIconVM
    {
    public:
        ModeIconVM() = default;

        ModeIconVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        ModeIconVM& setIcon(const s3d::Texture& icon)
        {
            m_icon = icon;
            return *this;
        }
        ModeIconVM& setIconOffset(const s3d::Vec2& offset)
        {
            m_iconOffset = offset;
            return *this;
        }
        ModeIconVM& setIconScale(double scale)
        {
            m_iconScale = scale;
            return *this;
        }

        ModeIconVM& setText(const s3d::String& text)
        {
            m_text = text;
            return *this;
        }
        ModeIconVM& setTextOffset(const s3d::Vec2& offset)
        {
            m_textOffset = offset;
            return *this;
        }
        ModeIconVM& setFontSize(double size)
        {
            m_fontSize = size;
            return *this;
        }

        ModeIconVM& setScale(double scale)
        {
            m_scale = scale;
            return *this;
        }

        ModeIconVM& setReverseColor(bool isReverseColor)
        {
            m_isReverseColor = isReverseColor;
            return *this;
        }
        ModeIconVM& setSelected(bool isSelected)
        {
            m_isSelected = isSelected;
            return *this;
        }
        void draw() const;
    private:
        s3d::Vec2 m_pos{};

        s3d::Texture m_icon;
        s3d::Vec2 m_iconOffset{};
        double m_iconScale = 1.0;

        s3d::String m_text{};
        s3d::Vec2 m_textOffset{};
        double m_fontSize = 40.0;

        double m_scale = 1.0;
        bool m_isReverseColor = false;

        bool m_isSelected = false;
    };
}
