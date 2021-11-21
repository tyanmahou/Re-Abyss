#include "Branch.hpp"
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Collision
{
	void Branch::onPreCollision()
	{
		m_result.onReflesh();
	}

	void Branch::onCollision(const Branch& other)
	{
		m_result.add(HitData{});
	}

	bool Branch::isCollision(const Branch& other) const
	{
		for (const auto& n1 : m_nodes) {
			for (const auto& n2 : other.m_nodes) {
				if (ColisionUtil::Intersects(n1->getShape(), n2->getShape())) {
					return true;
				}
			}
		}
		return false;
	}

}
