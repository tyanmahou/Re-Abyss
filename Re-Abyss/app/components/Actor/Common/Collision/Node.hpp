#pragma once
#include <abyss/modules/Collision/base/INode.hpp>
#include <abyss/components/Actor/Common/Collision/Collider/ICollider.hpp>

namespace abyss::Actor::Collision
{
	class Node : public abyss::Collision::INode
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