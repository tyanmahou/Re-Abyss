#pragma once
#include <functional>
#include <variant>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/IFolder.hpp>
#include <abyss/utils/DebugMenu/IValue.hpp>
#include <abyss/utils/DebugMenu/IFindable.hpp>

namespace abyss::DebugMenu
{
	class RadioButton:
		public INode,
		public IFolder,
		public IValue,
		public IFindable
	{
		class Item;
	public:
		using CallbackType = std::variant<
			std::function<void(size_t)>,
			std::function<void(s3d::StringView)>,
			std::function<void(size_t, s3d::StringView)>
		>;
	public:
		RadioButton() = default;
		RadioButton(
			const s3d::String& key,
			const CallbackType& callback = {}
		);
		RadioButton(
			const s3d::String & key,
			const s3d::String & label,
			const CallbackType& callback = {}
		);

		void addList(const s3d::String& value);
		void addList(const s3d::String& value, const s3d::String& label);

		void close();
	public:
		void onOpendUpdate() override;

		bool isOpened() const override
		{
			return m_isOpened;
		}
		Ref<IItem> focusItem() const override;
		s3d::Optional<size_t> focusIndex() const;
		const s3d::Array<std::shared_ptr<INode>>& childNodes() const
		{
			return m_childs;
		}
	public:
		s3d::StringView label() const override;

		void onFoucsUpdate() override;

	public:
		NodeValue value() const override;
	public:
		s3d::StringView key() const override
		{
			return m_key;
		}
	private:
		s3d::String m_key, m_label;
		s3d::Array<std::shared_ptr<IItem>> m_items;
		s3d::Array<std::shared_ptr<INode>> m_childs;
		bool m_isOpened = false;

		size_t m_selectIndex = 0;
		CallbackType m_callback;
	};
}