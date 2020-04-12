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
		Schield
	};
	struct EnemyEntity
	{
		EnemyType type;
		s3d::Vec2 pos;
		Forward forward;
	};
}