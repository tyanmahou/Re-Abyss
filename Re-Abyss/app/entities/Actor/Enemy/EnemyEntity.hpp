#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/values/Forward.hpp>

namespace abyss::Actor::Enemy
{
	enum class EnemyType
	{
		None,
		Slime,
		RollingTako,
		CaptainTako,
		Ikalien,
		LaunShark,
		Schield,
		Warrus,
        BabyDux,
        BazookaKun,

		// MidBoss
		KingDux,

		// Boss
		CodeZero,
	};
	struct EnemyEntity
	{
		s3d::uint32 id;
		EnemyType type;
		s3d::Vec2 pos;
        s3d::Vec2 footPos;
        Forward forward;
	};
}
