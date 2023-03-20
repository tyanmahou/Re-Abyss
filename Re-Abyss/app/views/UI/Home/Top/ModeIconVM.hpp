#pragma once
#include <memory>
#include <Siv3D/Vector2D.hpp>

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
        template<class ThumbType, class... Args> requires std::derived_from<ThumbType, IModeThumb>
        ModeIconVM& setLockThumbnail(Args&&... args)
        {
            return this->setLockThumbnail(std::make_unique<ThumbType>(std::forward<Args>(args)...));
        }
        ModeIconVM& setLockThumbnail(std::unique_ptr<IModeThumb> thumbnail)
        {
            m_lockThumbnail = std::move(thumbnail);
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

        std::unique_ptr<IModeThumb> m_lockThumbnail;
        std::unique_ptr<IModeThumb> m_thumbnail;

        double m_scale = 1.0;
        bool m_isReverseColor = false;

        bool m_isSelected = false;
        bool m_isLocked = false;
    };
}
