#include "CollisionModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss
{
	void SimpleCollision::collisionAll(const s3d::Array<Ref<IColliderModel>>& colliders)
	{
		// Collision
		auto prevCollision = std::move(this->m_currentCollision);
		this->m_currentCollision.clear();
		for (auto&& collider : colliders) {
			collider->onReflesh();
		}
		for (auto it1 = colliders.begin(); it1 != colliders.end(); ++it1) {
			if (!(*it1) || !(*it1)->isActive()) {
				continue;
			}
			for (auto it2 = it1 + 1; it2 != colliders.end(); ++it2) {
				if (!(*it2) || !(*it2)->isActive()) {
					continue;
				}
				if ((*it1)->getLayer() == (*it2)->getLayer()) {
					continue;
				}
				CollisionPairHash hash((*it1)->getId(), (*it2)->getId());
				if (ColisionUtil::Intersects((*it1)->getCollider(), (*it2)->getCollider())) {
					m_currentCollision.insert(hash);
					if (prevCollision.find(hash) == prevCollision.end()) {
						// onEnter
						(*it1)->onCollisionEnter((*it2)->getActor());
						(*it2)->onCollisionEnter((*it1)->getActor());
					}
					// onStay
					(*it1)->onCollisionStay((*it2)->getActor());
					(*it2)->onCollisionStay((*it1)->getActor());
				} else {
					if (prevCollision.find(hash) != prevCollision.end()) {
						// onExit
						(*it1)->onCollisionExit((*it2)->getActor());
						(*it2)->onCollisionExit((*it1)->getActor());
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

