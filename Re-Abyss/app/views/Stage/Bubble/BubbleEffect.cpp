#include "BubbleEffect.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/Camera.hpp>
namespace abyss
{
    BubbleEffect::BubbleEffect(Manager* pManager, const Vec2& offset, Small) :
        m_maxRadius(1),
        m_type(Type::Small),
        m_speed(0, Random(-72.0, -36.0)),
        m_deflection(Random(0.0, 400.0)),
        m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
        m_color(0.8, 0.5),
        m_pManager(pManager)
    {}

    BubbleEffect::BubbleEffect(Manager* pManager, const Vec2& offset, Middle) :
        m_type(Type::Middle),
        m_maxRadius(Random(10.0, 40.0)),
        m_speed(0, Random(-120.0, -6.0)),
        m_deflection(Random(0.0, 400.0)),
        m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
        m_color(0.5, 0.2),
        m_pManager(pManager)
    {}

    BubbleEffect::BubbleEffect(Manager* pManager, const Vec2& offset, Big) :
        m_type(Type::Big),
        m_maxRadius(Random(60.0, 120.0)),
        m_speed(Random(-50.0, 50.0), Random(-50.0, -30.0)),
        m_deflection(0),
        m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
        m_color(0.2, 0.2),
        m_pManager(pManager)
    {}
    bool BubbleEffect::update(double t)
    {
        ScopedRenderStates2D state(BlendState::Additive);

        double dt = m_pManager->getModule<GlobalTime>()->deltaTime();
        const double r = Min(m_maxRadius, EaseOut(Easing::Cubic, 0.0, m_maxRadius, t));
        m_pos += m_speed * dt;
        Vec2 pos = m_pos + Vec2{ m_deflection * Sin(t),0.0 };
        ColorF color = m_type == Type::Big ? m_color : m_color * Abs(Sin(t));
        Circle(pos, r).draw(color);

        return m_pManager->getModule<Camera>()->getCurrentRoom().getRegion().stretched(480, 520).intersects(pos);
    }

}
