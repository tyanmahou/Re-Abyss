#pragma once
#include <abyss/models/actors/Player/Shot/PlayerShotActor.hpp>

namespace abyss
{
	struct PlayerShotViewModel
	{
		PlayerShotActor::Type type;
		s3d::Vec2 pos;
		double r;
		Forward forward;
	};
}