#pragma once
#include <abyss/modules/ColSys/base/INode.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>

namespace abyss::Actor::Col
{
	class Node : public ColSys::INode
	{
	public:
		Node(Ref<ICollider> collider):
			m_collider(collider)
		{}
		CShape getShape() const override
		{
			if (!m_collider) {
				return s3d::none;
			}
			return m_collider->getCollider();
		}
	private:
		Ref<ICollider> m_collider;
	};
}