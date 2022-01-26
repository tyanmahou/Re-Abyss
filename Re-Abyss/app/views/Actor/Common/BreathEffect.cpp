#include <abyss/views/Actor/Common/BreathEffect.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    BreathEffect::BreathEffect(const Vec2& pos):
        m_pos(pos)
    {}

    bool BreathEffect::update(double t)
    {
        ScopedRenderStates2D blend(BlendState::Additive);

        auto pos = m_pos + Vec2{10 * Sin(t * 1.5), -60 * t};
        Circle(pos, 3).drawFrame(0.5, ColorF(0.5));
        return t < 10.0;
    }

}
