#include <abyss/views/UI/Home/Top/ModeIcon/GuildThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    GuildThumb::GuildThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void GuildThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"guild_off_inv").drawAt(pos, colors[1]);
        m_texture(U"guild_off").drawAt(pos, colors[0]);
    }
    void GuildThumb::drawUnselected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"guild_off_inv").drawAt(pos, colors[1]);
        m_texture(U"guild_on").drawAt(pos, colors[0]);
    }
}
