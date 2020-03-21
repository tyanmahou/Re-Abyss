#include "LightVM.hpp"

#include <Siv3D.hpp>
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
        const double sin0_1 = s3d::Periodic::Sine0_1(5s);
        const double alpha = Min(1.0, m_brightness * (0.4 + sin0_1 * 0.6) * 60 * Scene::DeltaTime());
        Circle(m_pos, m_range / 2.0 + 10 * sin0_1).draw(ColorF(1, alpha), outerColor);
    }
}
