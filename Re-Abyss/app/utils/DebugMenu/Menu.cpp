#include <abyss/utils/DebugMenu/Menu.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/utils/DebugMenu/RadioButton.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::DebugMenu
{
	Menu::Menu():
		m_root(std::make_shared<RootFolder>(U"DebugMenu")),
		m_skin(std::make_unique<DefaultSkin>())
	{
		{
			auto child = Node::Create<Folder>(U"NYAA");
			child.add(Node::Create<Button>(U"ButtonA", [] {Debug::Log << U"A"; }));
			child.add(Node::Create<Button>(U"ButtonB", [] {Debug::Log << U"B"; }));
			m_root.add(child);
		}
		m_root.add(Node::Create<Button>(U"ButtonC", [] {Debug::Log << U"C"; }));
		{
			auto child = Node::Create<Folder>(U"WAAAA", U"aaa");
			child.add(Node::Create<Button>(U"ButtonD", [] {Debug::Log << U"D"; }));
			child.add(Node::Create<BoolItem>(U"BoolE", U"チェック", false, [](bool a) {Debug::Log << U"E" << a; }));
			m_root.add(child);
		}
		{
			auto radioButtonNative = std::make_shared<RadioButton>(U"RadioButton", [](size_t index, s3d::StringView label) {
				Debug::Log << index << U": " << label;
			});
			radioButtonNative->addList(U"AAA");
			radioButtonNative->addList(U"BBB");
			radioButtonNative->addList(U"CCC");
			m_root.add(Node(radioButtonNative));
		}
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
}
