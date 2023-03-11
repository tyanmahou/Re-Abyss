#pragma once
#include <abyss/views/UI/Home/Top/ModeIcon/IModeThumb.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::Home::Top
{
    class MaintThumb : public IModeThumb
    {
    public:
        MaintThumb();
        void drawUnselected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const override;
        void drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const override;
    private:
        TexturePacker m_texture;
    };
}
