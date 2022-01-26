#include <abyss/views/Actor/Common/EnemyDeadEffect.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	EnemyDeadEffect::EnemyDeadEffect(const Vec2& pos) :
		m_pos(pos),
		m_texture(Resource::Assets::Main()->load(U"actors/Common/common_effects.json"))
	{}
	bool EnemyDeadEffect::update(double t)
	{
		m_animeIndex = static_cast<int32>(t * 12.0);

		if (m_animeIndex <= 6) {
			m_texture(U"enemy_dead")(40 * m_animeIndex, 0, 40, 40).drawAt(m_pos);
		}

		return m_animeIndex <= 6;
	}
}
