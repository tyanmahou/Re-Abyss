#pragma once
#include <abyss/modules/Collision/base/IExtension.hpp>

namespace abyss::Actor::Collision
{
	class Receiver final : public abyss::Collision::IExtension
	{
	public:
		struct Data{};
	public:
		abyss::Collision::ExtData data() const override
		{
			return Data{};
		}
	};
}