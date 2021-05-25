#pragma once

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IApplication
	{
	protected:
		virtual bool update() = 0;
	public:
        IApplication(const s3d::String& appName, s3d::Size windowSize);
		virtual ~IApplication();

		bool run();
	};
}