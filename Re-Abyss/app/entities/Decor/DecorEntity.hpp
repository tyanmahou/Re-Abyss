#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/entities/Decor/Motif.hpp>

namespace abyss::decor
{

	struct DecorEntity
	{
		s3d::uint32 id;
		DecorType type;
		s3d::Vec2 pos;
		s3d::Vec2 size;
		double rotation;
		bool isMirrored = false;
		bool isFlipped = false;
	};
}