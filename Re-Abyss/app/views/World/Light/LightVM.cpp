#include "LightVM.hpp"
#include <Siv3D/Circle.hpp>
#include <Siv3D/Color.hpp>

namespace abyss
{
    LightVM::LightVM(const s3d::Vec2& pos, double range, double brightness):
        m_pos(pos),
        m_range(range),
        m_brightness(brightness)
    {

    }

    void LightVM::draw() const
    {
        using namespace s3d;
        constexpr ColorF outerColor{ 1.0, 0.0 };

        Circle(m_pos, m_range * 2.5).draw(ColorF(1, m_brightness), outerColor);
        Circle(m_pos, m_range).draw(ColorF(1, m_brightness), outerColor);
    }
}
