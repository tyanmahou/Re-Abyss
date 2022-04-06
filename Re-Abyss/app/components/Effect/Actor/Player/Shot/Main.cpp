#include <abyss/components/Effect/Actor/Player/Shot/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Player::Shot
{
    Main::Main(
        EffectObj* pObj,
        const s3d::Vec2& pos,
        double radius,
        const s3d::ColorF& color
    ) :
        m_pObj(pObj),
        m_pos(pos),
        m_radius(radius),
        m_hsv(color)
    {
        double offset = Random<double>(0.0, 10.0);
        m_radius -= offset;

        m_hsv.h += 5 * offset;
    }
    bool Main::onDraw(double time)
    {
        ScopedRenderStates2D s(BlendState::Additive);
        double revT = 1.0 - time > 0 ? 1.0 - time : 0;
        double r = m_radius * revT;
        Circle(m_pos, r).draw(m_hsv.toColor(static_cast<uint32>(50.0 * revT)));

        if (auto pLight = m_pObj->getModule<Light>()) {
            pLight->addCircle(m_pos, r * 2.5, 1.0f - (1.0 - revT) * (1.0 - revT));
        }
        return time <= 1.0;
    }
}