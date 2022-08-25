#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Forward.hpp>

namespace abyss::Actor::Gimmick
{
	enum class GimmickType
	{
		None,
		StartPos,
		Door,
		Bulletin,
		Bush,
		EventTrigger,
		BgmChanger,
		CodeZeroBack,
	};
	struct GimmickEntity
	{
		s3d::uint32 id;
		GimmickType type;
		s3d::Vec2 pos;
	};
}