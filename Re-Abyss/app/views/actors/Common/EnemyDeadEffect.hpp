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

		EnemyDeadEffect(Vec2 pos) :
			m_pos(pos),
			m_texture(U"resources/images/actors/Common/enemy_dead.png")
		{}

		bool update(double t)override
		{
			m_animeIndex = static_cast<int32>(t * 12.0);

			if (m_animeIndex <= 6) {
				m_texture(40 * m_animeIndex, 0, 40, 40).drawAt(m_pos);
			}

			return m_animeIndex <= 6;
		}
	};
}