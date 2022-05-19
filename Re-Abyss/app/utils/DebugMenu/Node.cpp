#include <abyss/utils/DebugMenu/Node.hpp>
#include <abyss/utils/DebugMenu/IValue.hpp>
#include <abyss/utils/DebugMenu/Folder.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	class Node::Handle
	{
	public:
		Handle() = default;
		Handle(std::shared_ptr<INode> node):
			m_node(node)
		{
			if (auto pFolder = std::dynamic_pointer_cast<Folder>(node)) {
				m_pFolder = pFolder.get();
			}
			if (auto pValue = std::dynamic_pointer_cast<IValue>(node)) {
				m_pValue = pValue.get();
			}
		}
		void add(const std::shared_ptr<Handle>& child)
		{
			if (m_pFolder) {
				m_pFolder->add(child->m_node);

				if (auto findable = std::dynamic_pointer_cast<IFindable>(child->m_node)) {
					m_findableChilds[findable->key()] = child;
				}
			}
		}
		std::shared_ptr<Handle> find(s3d::StringView key)
		{
			std::shared_ptr<Handle> ret;

			Handle* handle = this;
			StringView::size_type startIndex = 0;
			StringView::size_type slashIndex = StringView::npos;
			do {
				startIndex = slashIndex + 1;
				slashIndex = key.indexOf(U'/', startIndex);
				if (auto&& child = handle->m_findableChilds[key.substr(startIndex, slashIndex - startIndex)]) {
					ret = child.lock();
					handle = ret.get();
				} else {
					return nullptr;
				}
			} while (slashIndex != s3d::StringView::npos);

			return ret;
		}
		NodeValue value() const
		{
			if (m_pValue) {
				return m_pValue->value();
			}
			return s3d::none;
		}
		INode* raw() const
		{
			return m_node.get();
		}
	private:
		std::shared_ptr<INode> m_node;
		s3d::HashTable<s3d::StringView, Ref<Handle>> m_findableChilds;

		Folder* m_pFolder = nullptr;
		IValue* m_pValue = nullptr;
	};

	Node::Node():
		Node(std::make_shared<Handle>())
	{
	}
	Node::Node(std::shared_ptr<INode> node):
		Node(std::make_shared<Handle>(node))
	{}
	Node::Node(std::shared_ptr<Handle> handle):
		m_pHandle(handle)
	{}
	void Node::add(const Node& child)
	{
		m_pHandle->add(child.m_pHandle);
	}
	Node Node::find(s3d::StringView key) const
	{
		if (auto handle = m_pHandle->find(key)) {
			return Node(handle);
		}
		return Node();
	}
	NodeValue Node::value() const
	{
		return m_pHandle->value();
	}
	INode* Node::raw() const
	{
		return m_pHandle->raw();
	}
}
