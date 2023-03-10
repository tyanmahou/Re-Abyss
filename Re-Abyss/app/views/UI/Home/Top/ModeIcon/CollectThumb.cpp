#include <abyss/views/UI/Home/Top/ModeIcon/CollectThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    CollectThumb::CollectThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void CollectThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]]double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"collect_on_inv").drawAt(pos, colors[0]);
        m_texture(U"collect_on").drawAt(pos, colors[1]);
    }
    void CollectThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"collect_off_inv").drawAt(pos, colors[0]);
        m_texture(U"collect_off").drawAt(pos, colors[1]);
    }
}
