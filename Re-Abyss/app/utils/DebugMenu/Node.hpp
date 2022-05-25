#pragma once
#include <memory>
#include <concepts>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/NodeValue.hpp>
#include <Siv3D/StringView.hpp>

namespace abyss::DebugMenu
{
	class Node
	{
		class Handle;
	public:
		template<class NodeType, class... Args>
		static Node Create(Args&&... args) requires std::derived_from<NodeType, INode> && std::constructible_from<NodeType, Args...>
		{
			return Node(std::make_shared<NodeType>(std::forward<Args>(args)...));
		}
	public:
		Node();
		explicit Node(std::shared_ptr<INode> node);

		void add(const Node& child);
		Node find(s3d::StringView key) const;

		NodeValue value() const;

		INode* raw() const;

		bool isValid() const;
		bool isValue() const;

		explicit operator bool() const
		{
			return this->isValid();
		}
	private:
		Node(std::shared_ptr<Handle> handle);
	private:
		std::shared_ptr<Handle> m_pHandle;
	};
}