#pragma once
#include "base/IApplication.hpp"

namespace abyss
{
	class MainApp : public IApplication
	{
	private:
		bool update() const override;
	public:
        MainApp();
		~MainApp() override;
	};
}