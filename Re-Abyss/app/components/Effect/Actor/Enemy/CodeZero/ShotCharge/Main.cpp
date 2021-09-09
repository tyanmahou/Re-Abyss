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
        for (auto _ : m_particleTimer.update(dt)) {
            const Vec2 v = Circular(Random(50.0, 160.0), Random(Math::TwoPi));
            const auto color = RandomBool() ? Palette::Red : Palette::Black;
            m_particles.emplace_back(m_pos + v, color);
        }

        // パーティクル移動
        for (auto& particle : m_particles) {
            auto toTarget = m_pos - particle.pos;
            if (!toTarget.isZero()) {
                toTarget.normalize();
            }
            particle.pos += toTarget * 120.0 * dt;
        }
    }

    void Main::onDraw(double time)
    {
        time = s3d::Saturate(time);

        for (const auto& particle : m_particles) {
            Circle(particle.pos, 1.5).draw(ColorF(particle.color).setA(1.0 - time));
        }
    }

    bool Main::isEnd() const
    {
        return m_pObj->updateTimeSec() >= 1.0;
    }
}