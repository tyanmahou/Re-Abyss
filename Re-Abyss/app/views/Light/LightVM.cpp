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

    void LightVM::draw(double time) const
    {
        const double sin0_1 = s3d::Periodic::Sine0_1(5s, time);
        const double alpha = s3d::Saturate(m_brightness * (0.4 + sin0_1 * 0.6));
        const double r = m_range / 2.0 + 10 * sin0_1;
        const double halfR = r / 2.0;
        Circle(m_pos, halfR)
            .drawShadow(Vec2::Zero(), halfR, halfR, ColorF(1.0, alpha));
    }
}
