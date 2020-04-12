#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss
{
	enum class GimmickType
	{
		None,
		StartPos,
		Door
	};
	struct GimmickEntity
	{
		GimmickType type;
		s3d::Vec2 pos;
	};
}