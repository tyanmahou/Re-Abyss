#include "EnemyDeadEffect.hpp"

#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss
{
	EnemyDeadEffect::EnemyDeadEffect(const Vec2& pos) :
		m_pos(pos),
		m_texture(ResourceManager::Main()->loadTexture(U"actors/Common/enemy_dead.png"))
	{}
	bool EnemyDeadEffect::update(double t)
	{
		m_animeIndex = static_cast<int32>(t * 12.0);

		if (m_animeIndex <= 6) {
			m_texture(40 * m_animeIndex, 0, 40, 40).drawAt(m_pos);
		}

		return m_animeIndex <= 6;
	}
}
