#pragma once
#include<Siv3D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	struct EnemyDeadEffect : IEffect
	{
	private:
		int32 m_animeIndex = 0;
		const Vec2 m_pos;
		TexturePacker m_texture;
	public:

		EnemyDeadEffect(const Vec2& pos);

		bool update(double t)override;
	};
}