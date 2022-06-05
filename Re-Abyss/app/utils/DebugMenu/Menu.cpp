#include <abyss/utils/DebugMenu/Menu.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/parser/MenuParser.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Menu Menu::FromXML(s3d::FilePathView path)
	{
		return Menu(MenuParser::FromXML(path, true));
	}
	Menu::Menu():
		m_root(std::make_shared<RootFolder>(U"DebugMenu")),
		m_skin(std::make_unique<DefaultSkin>())
	{
	}
	void Menu::update()
	{
		auto folder = dynamic_cast<IFolder*>(m_root.raw());
		while (folder) {
			if (auto focus = folder->focusItem()) {
				if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
					if (childFolder->isOpened()) {
						folder = childFolder.get();
						continue;
					}
				} 
			}
			break;
		}
		if (folder) {
			folder->onOpendUpdate();
			if (auto focus = folder->focusItem()) {
				focus->onFoucsUpdate();
			}
		}
	}
	void Menu::draw() const
	{
		m_skin->draw(dynamic_cast<RootFolder*>(m_root.raw()));
	}
	Menu::Menu(Node rootNode):
		m_root(rootNode),
		m_skin(std::make_unique<DefaultSkin>())
	{
	}
}
