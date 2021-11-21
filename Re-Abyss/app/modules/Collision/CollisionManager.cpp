#include "CollisionManager.hpp"
#include "SimpleDetection.hpp"
#include <abyss/modules/Collision/base/INode.hpp>

namespace abyss::Collision
{
	CollisionManager::CollisionManager():
		m_detection(std::make_shared<SimpleDetection>())
	{
	}
	s3d::uint64 CollisionManager::createId()
	{
		return m_idCounter.createId();
	}
	void CollisionManager::onCollision()
	{
		m_detection->collisionAll(m_nodes);
	}
	void CollisionManager::cleanUp()
	{
		s3d::Erase_if(m_nodes, [this](const std::shared_ptr<INode>& c) {
			return c->isDestroyed();
		});
	}
}

