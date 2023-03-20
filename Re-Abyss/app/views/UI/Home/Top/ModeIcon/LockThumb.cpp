#include <abyss/views/UI/Home/Top/ModeIcon/LockThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    LockThumb::LockThumb(double scale) :
        m_scale(scale),
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }

    void LockThumb::drawUnselected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"lock").scaled(m_scale).drawAt(pos, colors[1]);
    }
    void LockThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"lock").scaled(m_scale).drawAt(pos, colors[1]);
    }
}
