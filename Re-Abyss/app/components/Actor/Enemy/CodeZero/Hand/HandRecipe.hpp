#pragma once
#include <abyss/utils/Axis2/Axis2.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
	struct HandRecipe
	{
		Axis2 axis;
		double distance = 0;
		double rotateLimit = 0;

		static HandRecipe CreateLeftPhase1();
		static HandRecipe CreateRightPhase1();
		static HandRecipe CreateLeftPhase2();
		static HandRecipe CreateRightPhase2();
	};
}