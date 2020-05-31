#include "BubbleEffect.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
	BubbleEffect::BubbleEffect(const Vec2& offset):
		m_maxRadius(Random(40.0, 240.0)),
		m_speed(Random(-120.0, -6.0)),
		m_deflection(Random(0.0, 400.0)),
		m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
		m_color(0.5, 0.2)
	{}

	BubbleEffect::BubbleEffect(const Vec2& offset, Small) :
	m_maxRadius(1),
		m_speed(Random(-72.0, -36.0)),
		m_deflection(Random(0.0, 400.0)),
		m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
		m_color(0.8, 0.5)
	{}
	bool BubbleEffect::update(double t)
	{
		double dt = WorldTime::DeltaTime();
		const double r = Min(m_maxRadius, EaseOut(Easing::Cubic, 0.0, m_maxRadius, t));
		m_pos.y += m_speed * dt;
		Vec2 pos = m_pos + Vec2{ m_deflection * Sin(t),0.0 };
		Circle(pos, r).draw(m_color * Abs(Sin(t)));
		return m_pos.y + r >= 0;
	}

}
