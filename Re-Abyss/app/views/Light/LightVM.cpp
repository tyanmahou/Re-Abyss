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
        ScopedRenderStates2D scoped(BlendState(
            true,
            Blend::One,
            Blend::One,
            BlendOp::Max
        ));
        using namespace s3d;
        constexpr ColorF outerColor{ 0.0, 1.0 };
        const double sin0_1 = s3d::Periodic::Sine0_1(5s, time);
        const double alpha = Min(1.0, m_brightness * (0.4 + sin0_1 * 0.6));
        const double r = m_range / 2.0 + 10 * sin0_1;
        const double halfR = r / 2.0;
        Circle(m_pos, halfR).draw(Palette::White, ColorF(alpha, 1));
        Circle(m_pos, r)
            .drawFrame(halfR + 1.0, 0, ColorF(alpha, 1.0), outerColor);
    }
}
