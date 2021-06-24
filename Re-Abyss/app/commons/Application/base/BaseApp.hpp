#pragma once

#include <abyss/commons/Application/base/IApplication.hpp>

namespace abyss
{
	class BaseApp : public IApplication
	{
	protected:
		virtual bool update() = 0;
	public:
		BaseApp(const s3d::String& appName, s3d::Size windowSize);

		bool run() override;
	};
}