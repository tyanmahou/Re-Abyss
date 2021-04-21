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
        const double sin0_1 = s3d::Periodic::Sine0_1(2.0s, time);
        const double alpha = s3d::Saturate(m_brightness * (0.9 + sin0_1 * 0.1));
        const double r = m_range / 2.0 + 1 * sin0_1;
        const double maxAlphaR = r / 4.0f;
        Circle(m_pos, maxAlphaR)
            .drawShadow(Vec2::Zero(), r - maxAlphaR, maxAlphaR, ColorF(1.0, alpha));
    }
}
