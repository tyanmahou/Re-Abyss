#include <abyss/views/UI/Home/Top/ModeIcon/OptionThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    OptionThumb::OptionThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void OptionThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::OptionIcon();
        m_texture(U"option_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1])
            ;
    }
    void OptionThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        auto addScale = 1.0 + 0.1 * s3d::Saturate(time * 5);
        const auto& viewParam = ViewParam::OptionIcon();
        m_texture(U"option_off")
            .scaled(viewParam.iconScale * addScale)
            .rotated(s3d::Periodic::Sawtooth0_1(10s, time) * s3d::Math::TwoPi)
            .drawAt(pos + viewParam.iconOffset, colors[1])
            ;
    }
}
