#pragma once
#include<Siv3D.hpp>

namespace abyss
{
	struct BubbleEffect : IEffect
	{
		inline static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
		inline static constexpr Vec2 CreateRangeSize{ 1080,240 };

	private:
		double m_maxRadius;
		double m_speed;
		double m_deflection;
		Vec2 m_pos;
	public:
		BubbleEffect(const Vec2& offset = {0, 0}) :
			m_maxRadius(Random(40.0, 240.0)),
			m_speed(Random(-2.0, -0.5)),
			m_deflection(Random(0.0, 400.0)),
			m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize }))
		{}

		bool update(double t) override
		{
			t *= 10;
			constexpr Color color{ 250,255,210,100 };
			const double r = Min(m_maxRadius, EaseOut(Easing::Cubic,0.0, m_maxRadius,t));
			m_pos.y += m_speed;
			Vec2 pos = m_pos + Vec2{ m_deflection * Sin(t),0.0 };
			Circle(pos, r).draw(ColorF(0.5, 0.2));
			return m_pos.y + r >= 0;
		}
	};
}