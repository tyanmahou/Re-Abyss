#include <abyss/utils/DebugMenu/Root.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>

namespace abyss::DebugMenu
{
	Root::Root():
		m_rootFolder(std::make_shared<Folder>()),
		m_skin(std::make_unique<DefaultSkin>())
	{
		auto child = std::make_shared<Folder>();
		child->add(std::make_shared<Button>(U"ButtonA", [] {Print << U"A"; }));
		child->add(std::make_shared<Button>(U"ButtonB", [] {Print << U"B"; }));
		m_rootFolder->add(child);
		m_rootFolder->add(std::make_shared<Button>(U"ButtonC", [] {Print << U"C"; }));
	}
	void Root::update()
	{
		std::shared_ptr<IFolder> folder = m_rootFolder;
		while (folder) {
			if (auto focus = folder->focusItem()) {
				if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
					folder = childFolder;
				} else {
					break;
				}
			} else {
				break;
			}
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
		Transformer2D transformer(Mat3x2::Translate(10, 10), s3d::TransformCursor::Yes);
		const s3d::Array<s3d::StringView> labels{
			U"AAAAAA",
			U"BBB",
			U"CCCCCCC"
		};
		m_skin->draw(labels, 1);
	}
}
