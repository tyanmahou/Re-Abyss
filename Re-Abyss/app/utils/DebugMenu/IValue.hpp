#pragma once
#include <abyss/utils/DebugMenu/NodeValue.hpp>

namespace abyss::DebugMenu
{
	class IValue
	{
	public:
		virtual ~IValue() = default;
		virtual NodeValue value() const = 0;
        virtual void reset() = 0;
	};
}
