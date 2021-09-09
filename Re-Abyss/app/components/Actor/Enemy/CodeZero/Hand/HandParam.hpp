#pragma once
#include <abyss/utils/Axis2/Axis2.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
	struct HandParam
	{
		Axis2 axis;
		double distance = 0;
		double rotateLimit = 0;

		static HandParam CreateLeftPhase1();
		static HandParam CreateRightPhase1();
		static HandParam CreateLeftPhase2();
		static HandParam CreateRightPhase2();
	};
}