#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/NodeValue.hpp>
#include <Siv3D/StringView.hpp>

namespace abyss::DebugMenu
{
	class Node
	{
		class Handle;
	public:
		Node();
		Node(std::shared_ptr<INode> node);

		void add(const Node& child);
		Node find(s3d::StringView key) const;

		NodeValue value() const;

		INode* raw() const;

		bool isValid() const;
		bool isValue() const;
	private:
		Node(std::shared_ptr<Handle> handle);
	private:
		std::shared_ptr<Handle> m_pHandle;
	};
}