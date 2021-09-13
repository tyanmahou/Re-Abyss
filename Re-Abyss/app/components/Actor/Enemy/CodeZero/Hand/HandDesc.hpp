#pragma once
#include <abyss/utils/Axis2/Axis2.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
	struct HandDesc
	{
		Axis2 axis;
		double distance = 0;
		double rotateLimit = 0;

		static HandDesc CreateLeftPhase1();
		static HandDesc CreateRightPhase1();
		static HandDesc CreateLeftPhase2();
		static HandDesc CreateRightPhase2();
	};
}