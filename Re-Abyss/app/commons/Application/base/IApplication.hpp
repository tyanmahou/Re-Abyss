#pragma once

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IApplication
	{
	public:
		IApplication() = default;
		virtual ~IApplication() = default;

        virtual void onStartup() = 0;
        virtual bool onUpdate() = 0;
        virtual void onShutdown() = 0;
	};
}
