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
		TimeController* m_pTime;
	public:
		BubbleEffect(TimeController* pTime, const Vec2& offset = { 0, 0 });

		BubbleEffect(TimeController* pTime, const Vec2& offset, Small);

		bool update(double t) override;
	};
}