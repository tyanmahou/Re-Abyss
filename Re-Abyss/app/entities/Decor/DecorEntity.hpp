#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Decor/DecorType.hpp>

namespace abyss::Decor
{

	struct DecorEntity
	{
		s3d::uint32 id;
		s3d::uint32 gId;
		DecorType type;
		s3d::Vec2 pos;
		s3d::Vec2 size;
		double rotation = 0.0;
		bool isMirrored = false;
		bool isFlipped = false;
	};
}