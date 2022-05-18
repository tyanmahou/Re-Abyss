#include <abyss/utils/DebugMenu/Folder.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Folder::Folder(const s3d::String& key, const s3d::String& label):
		m_key(key),
		m_label(label)
	{}
	void Folder::add(std::shared_ptr<INode> child)
	{
		m_childs << child;
		if (auto pItem = std::dynamic_pointer_cast<IItem>(child)) {
			m_items << pItem;
		}
	}
	void Folder::onFoucsUpdate()
	{
		if (!m_isOpened && KeyZ.down()) {
			m_isOpened = true;
		}
	}
	void Folder::onOpendUpdate()
	{
		if (m_isOpened && KeyX.down()) {
			m_isOpened = false;
			return;
		}
		if (!m_items.isEmpty()) {
			if (KeyUp.down() && m_focusIndex > 0) {
				m_focusIndex -= 1;
			} else if (KeyDown.down() && m_focusIndex < m_items.size() - 1) {
				m_focusIndex += 1;
			}
			m_focusIndex = s3d::Clamp<size_t>(m_focusIndex, 0, m_items.size() - 1);
		}
	}
	Ref<IItem> Folder::focusItem() const
	{
		if (auto focusIndex = this->focusIndex()) {
			return m_items[*focusIndex];
		}
		return nullptr;
	}
	s3d::Optional<size_t> Folder::focusIndex() const
	{
		if (m_items.isEmpty()) {
			return s3d::none;
		}
		return m_focusIndex;
	}
}
