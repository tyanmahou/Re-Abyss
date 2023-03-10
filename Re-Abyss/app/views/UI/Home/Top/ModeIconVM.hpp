#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::Home::Top
{
    class IModeThumb;

    class ModeIconVM
    {
    public:
        ModeIconVM() = default;

        ModeIconVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        ModeIconVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        template<class ThumbType, class... Args> requires std::derived_from<ThumbType, IModeThumb>
        ModeIconVM& setThumbnail(Args&&... args)
        {
            return this->setThumbnail(std::make_unique<ThumbType>(std::forward<Args>(args)...));
        }
        ModeIconVM& setThumbnail(std::unique_ptr<IModeThumb> thumbnail)
        {
            m_thumbnail = std::move(thumbnail);
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
        double m_time = 0;

        std::unique_ptr<IModeThumb> m_thumbnail;

        s3d::String m_text{};
        s3d::Vec2 m_textOffset{};
        double m_fontSize = 40.0;

        double m_scale = 1.0;
        bool m_isReverseColor = false;

        bool m_isSelected = false;
    };
}
