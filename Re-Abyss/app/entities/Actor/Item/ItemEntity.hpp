#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Item
{
	enum class ItemType
	{
		None,
		Recovery,
	};

	struct ItemEntity
	{
		s3d::uint32 id;
		ItemType type;
		s3d::Vec2 pos;
	};
}