#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::Home::Top
{
    class IModeThumb;

    class ModeIconVM
    {
    public:
        ModeIconVM();

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
        ModeIconVM& setLocked(bool isLocked)
        {
            m_isLocked = isLocked;
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

        TexturePacker m_texture;
        std::unique_ptr<IModeThumb> m_thumbnail;

        double m_scale = 1.0;
        bool m_isReverseColor = false;

        bool m_isSelected = false;
        bool m_isLocked = false;
    };
}