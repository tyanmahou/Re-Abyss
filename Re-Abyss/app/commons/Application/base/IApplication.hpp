#pragma once

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IApplication
	{
	public:
		IApplication() = default;
		virtual ~IApplication() = default;

		virtual bool run() = 0;
	};
}