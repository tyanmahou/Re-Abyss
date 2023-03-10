#include <abyss/views/UI/Home/Top/ModeIcon/MemoryThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    MemoryThumb::MemoryThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void MemoryThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"memory_on_inv").drawAt(pos, colors[0]);
        m_texture(U"memory_on").drawAt(pos, colors[1]);
    }
    void MemoryThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"memory_off_inv").drawAt(pos, colors[0]);
        m_texture(U"memory_off").drawAt(pos, colors[1]);
    }
}
