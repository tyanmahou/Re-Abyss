#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/ChargeCircle.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    using namespace abyss::Actor::Enemy::CodeZero;

    ChargeCircle::ChargeCircle(EffectObj* pObj, const s3d::Vec2& pos):
        m_pObj(pObj),
        m_pos(pos)
    {
    }
    bool ChargeCircle::onDraw(double time)
    {
        auto tmp = static_cast<s3d::int32>(time * 10.0);
        double alpha = tmp % 2 ? 0.9 : 0.5;

        double prevRadius = m_radius;
        double rate = (1 - Periodic::Sawtooth0_1(0.6s, time));
        m_radius = 150 * rate;
        if (!(time <= ShotParam::Wait::ScaleTime || prevRadius < m_radius)) {
            return false;
        }
        Circle(m_pos, m_radius)
            .drawFrame(1, 1, ColorF(0.0, alpha));
        return true;
    }
}
