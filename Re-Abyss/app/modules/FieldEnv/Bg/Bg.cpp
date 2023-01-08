#include <abyss/modules/FieldEnv/Bg/Bg.hpp>
#include <Siv3D.hpp>

namespace abyss::FieldEnv
{
    Bg::Bg():
        m_bgColor(s3d::Palette::Black)
    {}
    void Bg::draw(const s3d::RectF& screen) const
    {
        screen.draw(m_bgColor);
    }
}
