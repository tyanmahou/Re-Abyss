#pragma once

#include<Siv3D/Fwd.hpp>

namespace abyss
{
	class Application
	{
	protected:
		virtual bool update() const = 0;
	public:
		Application(const s3d::String& appName, s3d::Size windowSize);
		virtual ~Application();

		bool run() const;
	};
}
