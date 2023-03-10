#include <abyss/views/UI/Home/Top/ModeIcon/SeekThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    SeekThumb::SeekThumb():
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void SeekThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"seek_off").drawAt(pos, colors[1]);
    }
    void SeekThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"seek_off").drawAt(pos, colors[1]);
    }
}
