#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss
{
	enum class GimmickType
	{
		None,
		StartPos,
		Door,
		EventTrigger,
	};
	struct GimmickEntity
	{
		s3d::uint32 id;
		GimmickType type;
		s3d::Vec2 pos;
	};
}