#pragma once

namespace abyss::Actor
{
	enum class DestoryTiming
	{
		CheckOut,
		CheckIn,
		Never,

		Default = CheckOut,
	};
}