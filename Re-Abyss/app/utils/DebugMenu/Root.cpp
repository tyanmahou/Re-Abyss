#include <abyss/utils/DebugMenu/Root.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::DebugMenu
{
	Root::Root():
		m_rootFolder(std::make_shared<RootFolder>(U"DebugMenu")),
		m_skin(std::make_unique<DefaultSkin>())
	{
		auto child = std::make_shared<Folder>(U"NYAA");
		child->add(std::make_shared<Button>(U"ButtonA", [] {Debug::Log << U"A"; }));
		child->add(std::make_shared<Button>(U"ButtonB", [] {Debug::Log << U"B"; }));
		m_rootFolder->add(child);
		m_rootFolder->add(std::make_shared<Button>(U"ButtonC", [] {Debug::Log << U"C"; }));
	}
	void Root::update()
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
	void Root::draw() const
	{
		Vec2 offset{ 10, 10 };
		std::shared_ptr<IFolder> folder = m_rootFolder;
		while (folder) {
			Transformer2D transformer(Mat3x2::Translate(offset), s3d::TransformCursor::Yes);
			m_skin->draw(folder.get());
			if (auto focus = folder->focusItem()) {
				if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
					if (childFolder->isOpened()) {
						folder = childFolder;
						offset += Vec2{ 100, 10 };
						continue;
					}
				}
			}

			break;
		}
	}
}
