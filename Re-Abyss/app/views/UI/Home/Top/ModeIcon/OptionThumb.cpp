#include <abyss/views/UI/Home/Top/ModeIcon/OptionThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    OptionThumb::OptionThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void OptionThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"option_off").drawAt(pos, colors[1]);
    }
    void OptionThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"option_off").drawAt(pos, colors[1]);
    }
}
