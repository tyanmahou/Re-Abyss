#pragma once

#include <abyss/commons/Application/base/IApplication.hpp>
#include <abyss/commons/Application/WindowCtrl.hpp>

namespace abyss
{
	class BaseApp : public IApplication
	{
	protected:
		virtual bool update() = 0;
	public:
		BaseApp(const s3d::String& appName, s3d::Size windowSize);

		bool run() override;

	protected:
		WindowCtrl m_windowCtrl;
	};
}