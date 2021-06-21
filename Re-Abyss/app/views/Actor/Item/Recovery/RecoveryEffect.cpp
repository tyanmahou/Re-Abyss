#include "RecoveryEffect.hpp"
#include <Siv3D.hpp>

namespace
{
    constexpr ColorF color0 = Color(14, 255, 51);
    constexpr ColorF color1 = Color(196, 255, 202);
}
namespace abyss::Actor::Item::Recovery
{
    struct RecoveryEffect::Impl
    {
        struct Particle
        {
        public:
            Particle(bool isFrame = false) :
                m_localPos(RandomVec2(Circle(40.0))),
                m_size(Random(4.0, 10.0)),
                m_angle(Random()* Math::TwoPi),
                m_isFrame(isFrame)
            {
                auto hsv = HSV(RandomBool() ? color0 : color1);
                hsv.s += 0.5;
                m_color = hsv.toColorF();
            }

            bool update(const Vec2& pos, double t)
            {
                constexpr double moveTime = 0.55;
                auto spreadRate = s3d::EaseOutCirc(s3d::Min(t, moveTime) / moveTime);
                auto newPos = pos + m_localPos * spreadRate;
                if (t >= 0.1) {
                    newPos += Vec2{ 0, -40.0 } * (t - moveTime);
                }
                {
                    auto rotateRate = spreadRate * 5.0;
                    if (t >= moveTime) {
                        rotateRate += (t - moveTime);
                    }
                    auto alpha = 1.0;
                    if (alpha >= moveTime) {
                        alpha = 1.0 - (t - moveTime) / (1.0 - moveTime);
                    }
                    Vec2 sizeVec2{ m_size * (1 - t), m_size  * (1 - t)};
                    auto quad = RectF(newPos - sizeVec2 / 2.0, sizeVec2)
                        .rotatedAt(newPos, m_angle + s3d::Math::TwoPi * rotateRate);
                    if (m_isFrame) {
                        quad.draw(m_color);
                    } else {
                        quad.drawFrame(1, m_color);
                    }
                }
                return t <= 1.0;
            }
        private:
            Vec2 m_localPos;
            double m_size;
            double m_angle;
            bool m_isFrame;
            ColorF m_color;
        };
        struct Circles
        {
        public:
            Circles():
                m_startAngle(Random()* Math::TwoPi)
            {}
            bool update(const Vec2& pos, double t)
            {
                auto colorFrame = static_cast<int32>(Periodic::Sawtooth0_1(0.25, t) * 2.0) % 2;
                {
                    auto rate = s3d::EaseOutQuart(t);
                    ColorF color = colorFrame ? color0 : color1;
                    Circle(pos, 36.0 * rate).drawArc(m_startAngle + s3d::Math::Pi - s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 1.0, color.setA(1.0 - rate));
                }
                {
                    auto rate = s3d::EaseOutExpo(t);
                    ColorF color = colorFrame ? color1 : color0;
                    Circle(pos, 40.0 * rate).drawArc(m_startAngle + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 2.0, 1.0, color.setA(1.0 - rate));
                }
                {
                    auto rate = s3d::EaseOutExpo(t);
                    ColorF color = colorFrame ? color0 : color1;
                    Circle(pos, 45.0 * rate).drawArc(m_startAngle + s3d::Math::HalfPi + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 0.0, color.setA(1.0 - rate));
                }
                {
                    auto rate = s3d::EaseOutQuad(t);
                    Circle(pos, 45.0 * rate).drawFrame(1.0, ColorF(1, 1.0 - rate));
                }
                return t <= 1.0;
            }
        private:
            double m_startAngle = 0.0;
        };
    public:
        Impl(const Ref<ILocator>& locator) :
            m_locator(locator)
        {
            if (m_locator) {
                m_pos = m_locator->getCenterPos();
            }

            for (auto count : step(1, 10)) {
                m_particles.emplace_back(count > 5);
            }
        }

        bool update(double t)
        {
            if (m_locator) {
                m_pos = m_locator->getCenterPos();
            }
            ScopedRenderStates2D blend(BlendState::Additive);

            bool result = m_circles.update(m_pos, t);
            for (auto&& particle : m_particles) {
                result |= particle.update(m_pos, t);
            }
            return result;
        }
    private:
        Ref<ILocator> m_locator;
        s3d::Vec2 m_pos;

        Circles m_circles;
        s3d::Array<Particle> m_particles;
    };
    RecoveryEffect::RecoveryEffect(const Ref<ILocator>& locator) :
        m_pImpl(std::make_unique<Impl>(locator))
    {
    }

    bool RecoveryEffect::update(double t)
    {
        return m_pImpl->update(t);
    }
}
