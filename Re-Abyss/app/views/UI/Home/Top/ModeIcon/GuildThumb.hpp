#pragma once
#include <abyss/views/UI/Home/Top/ModeIcon/IModeThumb.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Shader/Mask/MaskShader.hpp>

namespace abyss::UI::Home::Top
{
    class GuildThumb final: public IModeThumb
    {
    public:
        GuildThumb();
        void drawUnselected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const override;
        void drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const override;
    private:
        TexturePacker m_texture;
        MaskShader m_mask;
    };
}
