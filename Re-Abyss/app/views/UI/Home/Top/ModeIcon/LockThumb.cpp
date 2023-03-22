#include <abyss/views/UI/Home/Top/ModeIcon/LockThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    LockThumb::LockThumb(double scale) :
        m_scale(scale),
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }

    void LockThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]]double time, const s3d::ColorF(&colors)[2]) const
    {
        m_texture(U"lock").scaled(m_scale).drawAt(pos, colors[1]);
    }
    void LockThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto shake = 10 * s3d::Periodic::Triangle0_1(1.0, s3d::Min(s3d::Periodic::Sawtooth0_1(2.0, time + 1.8), 0.1) / 0.1);

        const auto rotate = s3d::ToRadians(shake);
        m_texture(U"lock")
            .scaled(m_scale)
            .rotated(rotate)
            .drawAt(pos, colors[1]);
    }
}
