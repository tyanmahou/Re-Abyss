#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>

namespace abyss::Effect
{
	class IDraw
	{
	public:
		virtual ~IDraw() = default;

		virtual DrawLayer getLayer() const = 0;
		virtual double getOrder() const = 0;
	};
}