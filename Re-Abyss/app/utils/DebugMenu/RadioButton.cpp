#include <abyss/utils/DebugMenu/RadioButton.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	class RadioButton::Item :
		public INode,
		public IItem
	{
	public:
		Item(
			RadioButton* parent,
			const s3d::String& value,
			const s3d::String& label
		):
			m_parent(parent),
			m_value(value),
			m_label(label)
		{

		}
	public:
		const s3d::String& value() const
		{
			return m_value;
		}
	public:
		s3d::StringView label() const override
		{
			return m_label;
		}

		void onFoucsUpdate() override
		{
			if (KeyZ.down()) {
				m_parent->close();
			}
		}
	private:
		RadioButton* m_parent;
		s3d::String m_value, m_label;
	};
	RadioButton::RadioButton(
		const s3d::String& key,
		const CallbackType& callback
	): 
		RadioButton(key, key, callback)
	{}

	RadioButton::RadioButton(
		const s3d::String& key,
		const s3d::String& label,
		const CallbackType& callback
	) :
		m_key(key),
		m_label(label),
		m_callback(callback)
	{}
	void RadioButton::addList(const s3d::String & value)
	{
		this->addList(value, value);
	}
	void RadioButton::addList(const s3d::String& value, const s3d::String& label)
	{
		auto item = std::make_shared<Item>(this, value, label);
		m_items << item;
		m_childs << item;
	}
	void RadioButton::close()
	{
		if (auto valueOpt = this->value().toIndexedStringOpt()) {
			auto [index, v] = *valueOpt;
			if (std::holds_alternative<std::function<void(size_t)>>(m_callback)) {
				if (auto&& callback = std::get<std::function<void(size_t)>>(m_callback)) {
					callback(index);
				}
			} else if (std::holds_alternative<std::function<void(s3d::StringView)>>(m_callback)) {
				if (auto&& callback = std::get<std::function<void(s3d::StringView)>>(m_callback)) {
					callback(v);
				}

			} else if (std::holds_alternative<std::function<void(size_t, s3d::StringView)>>(m_callback)) {
				if (auto&& callback = std::get<std::function<void(size_t, s3d::StringView)>>(m_callback)) {
					callback(index, v);
				}
			}
		}
	}
	void RadioButton::onOpendUpdate()
	{
		if (m_isOpened && KeyX.down()) {
			m_isOpened = false;
			return;
		}
		if (!m_items.isEmpty()) {
			if (KeyUp.down() && m_selectIndex > 0) {
				m_selectIndex -= 1;
			} else if (KeyDown.down() && m_selectIndex < m_items.size() - 1) {
				m_selectIndex += 1;
			}
			m_selectIndex = s3d::Clamp<size_t>(m_selectIndex, 0, m_items.size() - 1);
		}
	}
	Ref<IItem> RadioButton::focusItem() const
	{
		if (auto focusIndex = this->focusIndex()) {
			return m_items[*focusIndex];
		}
		return nullptr;
	}
	s3d::Optional<size_t> RadioButton::focusIndex() const
	{
		if (m_items.isEmpty()) {
			return s3d::none;
		}
		return m_selectIndex;
	}
	s3d::StringView RadioButton::label() const
	{
		if (auto focusItem = this->focusItem()) {
			return U"{}: {}"_fmt(m_label, focusItem->label());
		}
		return m_label;
	}
	void RadioButton::onFoucsUpdate()
	{
		if (!m_isOpened && KeyZ.down()) {
			m_isOpened = true;
		}

		//if (!m_items.isEmpty()) {
		//	if (KeyLeft.down() && m_selectIndex > 0) {
		//		m_selectIndex -= 1;
		//	} else if (KeyRight.down() && m_selectIndex < m_items.size() - 1) {
		//		m_selectIndex += 1;
		//	}
		//	m_selectIndex = s3d::Clamp<size_t>(m_selectIndex, 0, m_items.size() - 1);
		//}
	}
	NodeValue RadioButton::value() const
	{
		auto&& index = this->focusIndex();
		if (index) {
			return s3d::none;
		}
		const s3d::String& value = std::dynamic_pointer_cast<const Item>(m_items[*index])->value();
		return std::pair<size_t, s3d::StringView>{*index, value};
	}
}
