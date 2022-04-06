#include <abyss/components/Effect/Actor/Player/ShotFiring/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Player::ShotFiring
{
    Main::Main(
        EffectObj* pObj,
        const s3d::Vec2& pos,
        double radius,
        const s3d::ColorF& color
    ) :
        m_pObj(pObj),
        m_pos(pos),
        m_radius(radius * radius / 2.0),
        m_color(color)
    {}
    bool Main::onDraw(double time)
    {
        time *= 1.7;
        ScopedRenderStates2D s(BlendState::Additive);
        double rate = EaseOut(Easing::Quint, time);
        Color color = m_color.setA(static_cast<uint32>(128.0 * Max(1 - time, 0.0)));
        Circle(m_pos, rate * m_radius).drawFrame(1, 1, color);
        return time <= 1.0;
    }
}