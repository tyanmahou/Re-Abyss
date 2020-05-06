#include "BubbleEffect.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
	bool BubbleEffect::update(double t)
	{
		double dt = WorldTime::DeltaTime();
		constexpr Color color{ 250,255,210,100 };
		const double r = Min(m_maxRadius, EaseOut(Easing::Cubic, 0.0, m_maxRadius, t));
		m_pos.y += m_speed * dt;
		Vec2 pos = m_pos + Vec2{ m_deflection * Sin(t),0.0 };
		Circle(pos, r).draw(m_color * Abs(Sin(t)));
		return m_pos.y + r >= 0;
	}

}
