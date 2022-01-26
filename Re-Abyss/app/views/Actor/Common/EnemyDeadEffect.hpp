#pragma once
#include <Siv3D/IEffect.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	struct EnemyDeadEffect : s3d::IEffect
	{
	private:
		s3d::int32 m_animeIndex = 0;
		const s3d::Vec2 m_pos;
		TexturePacker m_texture;
	public:

		EnemyDeadEffect(const s3d::Vec2& pos);

		bool update(double t)override;
	};
}