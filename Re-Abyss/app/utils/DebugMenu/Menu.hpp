#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <abyss/utils/DebugMenu/Node.hpp>

namespace abyss::DebugMenu
{
	class Menu
	{
	public:
		static Menu FromXML(s3d::FilePathView path);
	public:
		Menu();

		void update();
		void draw() const;

		const Node& root() const
		{
			return m_root;
		}
	private:
		Menu(Node rootNode);
	private:
		Node m_root;
		std::unique_ptr<ISkin> m_skin;
	};
}