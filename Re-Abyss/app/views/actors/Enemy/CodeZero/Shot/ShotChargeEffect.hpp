#pragma once
#include <Siv3D.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
namespace abyss::CodeZero::Shot
{
    struct ShotChargeEffect : IEffect
    {
        struct Particle
        {
            Vec2 m_pos;
            ColorF m_color;
            Particle() = default;
            Particle(const Vec2& pos, const ColorF& color) :
                m_pos(pos),
                m_color(color)
            {}
        };

        Array<Particle> m_particles;

        //エフェクトの中心
        Vec2 m_pos;
        s3d::int32 m_count = 140;
        GlobalTime* m_pTime;
        ShotChargeEffect(GlobalTime* pTime, const Vec2& pos) :
            m_pos(pos),
            m_pTime(pTime)
        {}

        bool update(double t) override
        {
            t *= 0.333;
            double dt = m_pTime->deltaTime();
            const bool isPaused = m_pTime->isPuase();
            if (!isPaused) {
                if (m_count > 0) {
                    const Vec2 v = Circular(Random(50.0, 160.0), Random(Math::TwoPi));
                    const auto color = RandomBool() ? Palette::Red : Palette::Black;
                    m_particles.emplace_back(m_pos + v, color);
                }
                m_count--;
            }
            for (auto& particle : m_particles) {
                if (!isPaused) {
                    Vec2 sa;
                    sa.x = m_pos.x - particle.m_pos.x;
                    sa.y = m_pos.y - particle.m_pos.y;

                    double angle = Math::Atan2(sa.y, sa.x);

                    particle.m_pos.x += 120.0 * Cos(angle) * dt;
                    particle.m_pos.y += 120.0 * Sin(angle) * dt;
                }
                Circle(particle.m_pos, 1.5).draw(particle.m_color.setA(1.0 - t));

            }
            return t < 1.0;
        }
    };
}