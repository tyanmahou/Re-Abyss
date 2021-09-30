#include "Main.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos):
        m_pObj(pObj),
        m_pos(pos),
        m_particleTimer(0.025s, 140)
    {}

    void Main::onUpdate()
    {
        double dt = m_pObj->deltaTime();
        m_particleTimer.update(dt).each([&](double) {
            const Vec2 v = Circular(Random(50.0, 160.0), Random(Math::TwoPi));
            const auto color = RandomBool() ? Palette::Red : Palette::Black;
            m_particles.emplace_back(m_pos + v, color);
        });

        // パーティクル移動
        for (auto& particle : m_particles) {
            auto toTarget = m_pos - particle.pos;
            if (!toTarget.isZero()) {
                toTarget.normalize();
            }
            particle.pos += toTarget * 120.0 * dt;
        }
    }

    bool Main::onDraw(double time)
    {
        auto rate = s3d::Saturate(time / 3.0);

        for (const auto& particle : m_particles) {
            Circle(particle.pos, 2.0).draw(ColorF(particle.color).setA(1.0 - rate));
        }
        return time <= 3.0;
    }
}