#pragma once

#include <abyss/commons/Application/base/IApplication.hpp>
#include <abyss/commons/Application/WindowCtrl.hpp>

namespace abyss
{
	class BaseApp : public IApplication
	{
	public:
		BaseApp(const s3d::String& appName, s3d::Size windowSize);

        bool run();
	protected:
		WindowCtrl m_windowCtrl;
	};
}
