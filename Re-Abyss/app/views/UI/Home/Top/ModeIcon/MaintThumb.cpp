#include <abyss/views/UI/Home/Top/ModeIcon/MaintThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    MaintThumb::MaintThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void MaintThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"maint_off").drawAt(pos, colors[1]);
    }
    void MaintThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"maint_off").drawAt(pos, colors[1]);
    }
}
