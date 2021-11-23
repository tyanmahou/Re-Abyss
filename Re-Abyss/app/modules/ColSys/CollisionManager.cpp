#include "CollisionManager.hpp"
#include "SimpleDetection.hpp"
#include <abyss/modules/ColSys/Branch.hpp>

namespace abyss::ColSys
{
	CollisionManager::CollisionManager():
		m_detection(std::make_shared<SimpleDetection>())
	{
	}
	s3d::uint64 CollisionManager::createId()
	{
		return m_idCounter.createId();
	}
	Ref<Branch> CollisionManager::add(s3d::uint64 id)
	{
		auto branch = std::make_shared<Branch>(id);
		m_reserves << branch;
		return branch;
	}
	void CollisionManager::onCollision()
	{
		for (auto&& branch : m_branchs) {
			branch->onPreCollision();
		}
		m_detection->collisionAll(m_branchs);
	}
	void CollisionManager::cleanUp()
	{
		if (!m_reserves.empty()) {
			for (auto& branch : m_reserves) {
				m_branchs << branch;
			}
			m_reserves.clear();
		}
		s3d::Erase_if(m_branchs, [this](const std::shared_ptr<Branch>& b) {
			return b->isDestroyed();
		});
	}
}

