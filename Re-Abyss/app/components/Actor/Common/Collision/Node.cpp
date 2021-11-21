#include "Node.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Collision
{
	Node::Node(ActorObj* pActor, s3d::uint64 id):
		m_pActor(pActor),
		m_id(id)
	{}

	bool Node::isActive() const
	{
		return m_isActive &&
			!m_isDestroyed &&
			m_pActor->isActive();
	}

	const CShape& Node::getShape() const
	{
		return {};
	}
	void Node::onPreCollision()
	{

	}
	void Node::onCollision(const Ref<INode>& other)
	{

	}
}