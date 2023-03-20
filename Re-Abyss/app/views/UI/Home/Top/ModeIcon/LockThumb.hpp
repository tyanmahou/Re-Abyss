#pragma once
#include <abyss/views/UI/Home/Top/ModeIcon/IModeThumb.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::Home::Top
{
    class LockThumb final : public IModeThumb
    {
    public:
        LockThumb(double scale);
        void drawUnselected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const = 0;
        void drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const = 0;
    private:
        TexturePacker m_texture;
        double m_scale;
    };
}
