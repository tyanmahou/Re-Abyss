#include <abyss/utils/DebugMenu/Menu.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::DebugMenu
{
	Menu::Menu():
		m_rootFolder(std::make_shared<RootFolder>(U"DebugMenu")),
		m_skin(std::make_unique<DefaultSkin>())
	{
		{
			auto child = std::make_shared<Folder>(U"NYAA");
			child->add(std::make_shared<Button>(U"ButtonA", [] {Debug::Log << U"A"; }));
			child->add(std::make_shared<Button>(U"ButtonB", [] {Debug::Log << U"B"; }));
			m_rootFolder->add(child);
		}
		m_rootFolder->add(std::make_shared<Button>(U"ButtonC", [] {Debug::Log << U"C"; }));
		{
			auto child = std::make_shared<Folder>(U"WANNN");
			child->add(std::make_shared<Button>(U"ButtonD", [] {Debug::Log << U"D"; }));
			child->add(std::make_shared<Button>(U"ButtonE", [] {Debug::Log << U"E"; }));
			m_rootFolder->add(child);
		}
	}
	void Menu::update()
	{
		std::shared_ptr<IFolder> folder = m_rootFolder;
		while (folder) {
			if (auto focus = folder->focusItem()) {
				if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
					if (childFolder->isOpened()) {
						folder = childFolder;
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
		m_skin->draw(m_rootFolder.get());
	}
}
