#pragma once
#include<Siv3D/Vector2D.hpp>

namespace abyss
{
	enum class EnemyType
	{
		None,
		Slime,
	};
	struct EnemyEntity
	{
		EnemyType type;
		s3d::Vec2 pos;
	};
}