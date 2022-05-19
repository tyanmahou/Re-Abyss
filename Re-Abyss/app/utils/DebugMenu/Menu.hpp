#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/Node.hpp>

namespace abyss::DebugMenu
{
	class Menu
	{
	public:
		Menu();

		void update();
		void draw() const;
	private:
		Node m_root;
		std::unique_ptr<ISkin> m_skin;
	};
}