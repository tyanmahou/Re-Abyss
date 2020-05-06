#pragma once
#include <Siv3D.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
	struct BubbleEffect : IEffect
	{
		struct Small{};
		inline static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
		inline static constexpr Vec2 CreateRangeSize{ 1080,240 };

	private:
		double m_maxRadius;
		double m_speed;
		double m_deflection;
		Vec2 m_pos;
		ColorF m_color;
	public:
		BubbleEffect(const Vec2& offset = {0, 0}) :
			m_maxRadius(Random(40.0, 240.0)),
			m_speed(Random(-120.0, -6.0)),
			m_deflection(Random(0.0, 400.0)),
			m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
			m_color(0.5, 0.2)
		{}

		BubbleEffect(const Vec2& offset, Small) :
			m_maxRadius(Random(2, 3)),
			m_speed(Random(-72.0, -36.0)),
			m_deflection(Random(0.0, 400.0)),
			m_pos(s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize })),
			m_color(1.0, 0.9)
		{}

		bool update(double t) override;
	};
}