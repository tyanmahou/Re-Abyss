#include <abyss/utils/DebugMenu/Menu.hpp>
#include <abyss/utils/DebugMenu/DefaultController.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/parser/MenuParser.hpp>
#include <abyss/utils/DebugMenu/Save/JSONSave.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Menu Menu::FromXML(s3d::FilePathView path)
	{
		return Menu(MenuParser::FromXML(path, true));
	}
	Menu::Menu():
        Menu(Node(std::make_shared<RootFolder>(U"DebugMenu")))
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
			folder->onOpendUpdate(m_input.get());
			if (auto focus = folder->focusItem()) {
				focus->onFoucsUpdate(m_input.get());
			}
		}
	}
	void Menu::draw() const
	{
		m_skin->draw(dynamic_cast<RootFolder*>(m_root.raw()));
	}
    bool Menu::load(const s3d::FilePath& path)
    {
        JSONSave saver(path);
        return saver.load(dynamic_cast<RootFolder*>(m_root.raw()));
    }
    bool Menu::save(const s3d::FilePath& path) const
    {
        JSONSave saver(path);
        return saver.save(dynamic_cast<RootFolder*>(m_root.raw()));
    }
    Menu::Menu(Node rootNode):
		m_root(rootNode),
        m_input(std::make_unique<DefaultController>()),
		m_skin(std::make_unique<DefaultSkin>())
	{
	}
}
