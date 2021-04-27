#pragma once
#include<Siv3D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	struct BreathEffect : IEffect
	{
	private:
		Vec2 m_pos;
	public:

		BreathEffect(const Vec2& pos);

		bool update(double t)override;
	};
}