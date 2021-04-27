#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss
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

		// Boss
		CodeZero,
	};
	struct EnemyEntity
	{
		s3d::uint32 id;
		EnemyType type;
		s3d::Vec2 pos;
		Forward forward;
	};
}