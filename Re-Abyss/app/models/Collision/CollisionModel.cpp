﻿#include "CollisionModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/utils/Collision/Collision.hpp>

namespace abyss
{
	void SimpleCollision::collisionAll(const s3d::Array<std::shared_ptr<IActor>>& objects)
	{
		// Collision
		auto prevCollision = std::move(this->m_currentCollision);
		this->m_currentCollision.clear();

		for (auto it1 = objects.begin(); it1 != objects.end(); ++it1) {
			for (auto it2 = it1 + 1; it2 != objects.end(); ++it2) {
				if ((*it1)->getTag() == (*it2)->getTag()) {
					continue;
				}
				CollisionPairHash hash((*it1)->getId(), (*it2)->getId());
				if (abyss::Intersects((*it1)->getCollider(), (*it2)->getCollider())) {
					m_currentCollision.insert(hash);
					if (prevCollision.find(hash) != prevCollision.end()) {
						// onEnter
						(*it1)->onCollisionEnter(it2->get());
						(*it2)->onCollisionEnter(it1->get());
					}
					// onStay
					(*it1)->onCollisionStay(it2->get());
					(*it2)->onCollisionStay(it1->get());
				} else {
					if (prevCollision.find(hash) == prevCollision.end()) {
						// onExit
						(*it1)->onCollisionExit(it2->get());
						(*it2)->onCollisionExit(it1->get());
					}
				}
			}
		}
	}
	void SimpleCollision::reset()
	{
		m_currentCollision.clear();
	}
}
