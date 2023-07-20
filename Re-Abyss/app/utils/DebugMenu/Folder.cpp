#include <abyss/utils/DebugMenu/Folder.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Folder::Folder(const s3d::String& key):
		Folder(key, key)
	{
	}
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
        if (auto pFindable = std::dynamic_pointer_cast<IFindable>(child)) {
            m_findChild.emplace(pFindable->key(), child);
        }
	}
	void Folder::onFoucsUpdate(const IInputController* input)
	{
		if (!m_isOpened && input->decide()) {
			m_isOpened = true;
		}
	}
	void Folder::onOpendUpdate(const IInputController* input)
	{
		if (m_isOpened && input->back()) {
			m_isOpened = false;
			return;
		}
		if (!m_items.isEmpty()) {
			if (input->up() && m_focusIndex > 0) {
				m_focusIndex -= 1;
			} else if (input->down() && m_focusIndex < m_items.size() - 1) {
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
    std::shared_ptr<INode> Folder::findChild(const s3d::String& key) const
    {
        auto it = m_findChild.find(key);
        if (it != m_findChild.end()) {
            return it->second;
        }
        return nullptr;
    }
}
