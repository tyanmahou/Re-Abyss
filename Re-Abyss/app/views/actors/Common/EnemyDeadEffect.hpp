#pragma once
#include<Siv3D.hpp>

namespace abyss
{
	struct EnemyDeadEffect : IEffect
	{
	private:
		int32 m_animeIndex = 0;
		const Vec2 m_pos;
		Texture m_texture;
	public:

		EnemyDeadEffect(const Vec2& pos);

		bool update(double t)override;
	};
}