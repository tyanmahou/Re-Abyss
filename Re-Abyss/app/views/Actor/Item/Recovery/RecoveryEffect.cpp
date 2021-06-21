#include "RecoveryEffect.hpp"
#include <Siv3D.hpp>
namespace abyss::Actor::Item::Recovery
{
    RecoveryEffect::RecoveryEffect(const Ref<ILocator>& locator):
        m_locator(locator),
        m_startAngle(Random() * Math::TwoPi)
    {
        if (m_locator) {
            m_pos = m_locator->getCenterPos();
        }
    }

    bool RecoveryEffect::update(double t)
    {
        if (m_locator) {
            m_pos = m_locator->getCenterPos();
        }
        ScopedRenderStates2D blend(BlendState::Additive);

        constexpr ColorF color0 = Color(14, 255, 51);
        constexpr ColorF color1 = Color(196, 255, 202);
        auto colorFrame = static_cast<int32>(Periodic::Sawtooth0_1(0.25, t) * 2.0) % 2;
        {
            auto rate = s3d::EaseOutQuart(t);
            ColorF color = colorFrame ? color0 : color1;
            Circle(m_pos, 36.0 * rate).drawArc(m_startAngle + s3d::Math::Pi - s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 1.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutExpo(t);
            ColorF color = colorFrame ? color1 : color0;
            Circle(m_pos, 40.0 * rate).drawArc(m_startAngle + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 2.0, 1.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutExpo(t);
            ColorF color = colorFrame ? color0 : color1;
            Circle(m_pos, 45.0 * rate).drawArc(m_startAngle + s3d::Math::HalfPi + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 0.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutQuad(t);
            Circle(m_pos, 45.0 * rate).drawFrame(1.0, ColorF(1, 1.0 - rate));
        }
        return t <= 1.0;
    }
}
