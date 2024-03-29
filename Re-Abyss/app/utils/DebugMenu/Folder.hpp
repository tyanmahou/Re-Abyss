#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/IFolder.hpp>
#include <abyss/utils/DebugMenu/IFindable.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>

namespace abyss::DebugMenu
{
	class Folder :
		public INode,
		public IFolder,
		public IFindable
	{
	public:
		Folder() = default;
		Folder(
			const s3d::String& key
		);
		Folder(
			const s3d::String & key,
			const s3d::String & label
		);

		void add(std::shared_ptr<INode> child);
	public:
		s3d::StringView key() const override
		{
			return m_key;
		}
	public:
		s3d::StringView label() const override
		{
			return m_label;
		}
		void onFoucsUpdate(const IInputController* input) override;
	public:
		void onOpendUpdate(const IInputController* input) override;

		bool isOpened() const override
		{
			return m_isOpened;
		}
		Ref<IItem> focusItem() const override;
		s3d::Optional<size_t> focusIndex() const override;
		const s3d::Array<std::shared_ptr<INode>>& childNodes() const
		{
			return m_childs;
		}
        std::shared_ptr<INode> findChild(const s3d::String& key) const;
	private:
		s3d::String m_key, m_label;
		s3d::Array<std::shared_ptr<IItem>> m_items;
		s3d::Array<std::shared_ptr<INode>> m_childs;
        s3d::HashTable<s3d::String, std::shared_ptr<INode>> m_findChild;
		bool m_isOpened = false;
		size_t m_focusIndex = 0;
	};
}
