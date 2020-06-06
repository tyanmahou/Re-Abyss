#pragma once
#include <Siv3D.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
	struct BubbleEffect : IEffect
	{
		struct Big{};
		struct Middle{};
		struct Small{};
		inline static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
		inline static constexpr Vec2 CreateRangeSize{ 1080,240 };

		enum class Type
		{
			Big,
			Middle,
			Small
		};
	private:
		Type m_type;
		double m_maxRadius;
		Vec2 m_speed;
		double m_deflection;
		Vec2 m_pos;
		ColorF m_color;
		TimeController* m_pTime;
	public:
		BubbleEffect(TimeController* pTime, const Vec2& offset, Small);
		BubbleEffect(TimeController* pTime, const Vec2& offset, Middle = {});
		BubbleEffect(TimeController* pTime, const Vec2& offset, Big);

		bool update(double t) override;
	};
}