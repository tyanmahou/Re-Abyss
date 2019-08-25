#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
	struct BackGroundEntity
	{
		s3d::Texture texture;
		s3d::Vec2 offset;

		s3d::Vector2D<bool> loop;
		s3d::Vec2 rate;
	};
}