#include "LightVM.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
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
        const double alpha = Min(1.0, m_brightness * (0.4 + sin0_1 * 0.6) * 60 * WorldTime::DeltaTime());
        const double r = m_range / 2.0 + 10 * sin0_1;
        Circle(m_pos, r / 2.0).draw(Palette::White, ColorF(1, alpha));
        Circle(m_pos, r)
            .drawFrame(r/2.0,0, ColorF(1, alpha), outerColor);
    }
}
