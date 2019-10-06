#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IView
	{
	public:
		virtual ~IView() = default;
		virtual void update() {};
		virtual void draw()const = 0;
	};
}