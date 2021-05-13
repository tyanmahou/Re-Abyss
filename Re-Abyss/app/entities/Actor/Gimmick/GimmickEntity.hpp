#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss::Actor::Gimmick
{
	enum class GimmickType
	{
		None,
		StartPos,
		Door,
		EventTrigger,
		BgmChanger,
	};
	struct GimmickEntity
	{
		s3d::uint32 id;
		GimmickType type;
		s3d::Vec2 pos;
	};
}