#include <abyss/utils/DebugMenu/RadioButton.hpp>
#include <abyss/utils/DebugMenu/HrItem.hpp>
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

		void onFoucsUpdate(const IInputController* input) override
		{
			if (input->decide()) {
				m_parent->close();
			}
		}
	private:
		RadioButton* m_parent;
		s3d::String m_value, m_label;
	};
	RadioButton::RadioButton(
		const s3d::String& key,
        size_t initSelect,
		const CallbackType& callback
	): 
		RadioButton(key, key, initSelect, callback)
	{}

	RadioButton::RadioButton(
		const s3d::String& key,
		const s3d::String& label,
         size_t initSelect,
		const CallbackType& callback
	) :
		m_key(key),
		m_label(label),
		m_callback(callback),
        m_initSelectIndex(initSelect)
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
	void RadioButton::addHr()
	{
        m_childs << std::make_shared<HrItem>();
	}
	void RadioButton::close()
	{
		m_isOpened = false;
        this->setSelect(m_focusIndex);
	}
    void RadioButton::setSelect(size_t select)
    {
        m_selectIndex = select;
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
	void RadioButton::onOpendUpdate(const IInputController* input)
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
		return m_focusIndex;
	}
	s3d::StringView RadioButton::label() const
	{
		return m_label;
	}
	void RadioButton::onFoucsUpdate(const IInputController* input)
	{
		if (!m_isOpened && input->decide()) {
			m_isOpened = true;
			m_focusIndex = m_selectIndex;
		}
	}
	NodeValue RadioButton::value() const
	{
		if (m_items.isEmpty()) {
			return s3d::none;
		}
		const s3d::String& value = std::dynamic_pointer_cast<const Item>(m_items[m_selectIndex])->value();
		return std::pair<size_t, s3d::StringView>{m_selectIndex, value};
	}
    void RadioButton::reset()
    {
        this->setSelect(m_initSelectIndex);
    }
}
