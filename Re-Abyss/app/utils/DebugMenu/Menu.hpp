#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>

namespace abyss::DebugMenu
{
	class Menu
	{
	public:
		Menu();

		void update();
		void draw() const;
	private:
		std::shared_ptr<RootFolder> m_rootFolder;
		std::unique_ptr<ISkin> m_skin;
	};
}