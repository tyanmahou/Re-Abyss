#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <abyss/utils/DebugMenu/Folder.hpp>

namespace abyss::DebugMenu
{
	class Root
	{
	public:
		Root();

		void update();
		void draw() const;
	private:
		std::shared_ptr<Folder> m_rootFolder;
		std::unique_ptr<ISkin> m_skin;
	};
}