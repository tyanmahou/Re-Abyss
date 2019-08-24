#pragma once
#include "../../IView.hpp"

namespace abyss
{
	class IWorldObjectView : public IView
	{
	public:
		virtual bool isDelete() const = 0;
	};
}