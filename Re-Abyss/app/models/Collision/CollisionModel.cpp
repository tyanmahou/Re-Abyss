#include "CollisionModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

namespace abyss
{
	void SimpleCollision::collisionAll(const s3d::Array<Ref<Actor::ICollider>>& colliders)
	{
		// Collision
		auto prevCollision = std::move(this->m_currentCollision);
		this->m_currentCollision.clear();
		for (auto&& collider : colliders) {
			collider->onReflesh();
		}

		s3d::Array<Ref<Actor::ICollider>> actColliders;
		actColliders.reserve(colliders.size());
		s3d::Array<Ref<Actor::ICollider>> mapColliders;
		mapColliders.reserve(colliders.size());

		for (const auto& col : colliders) {
			if (!col || !col->isActive()) {
				continue;
			}
			if (col->getLayer() == LayerGroup::Map) {
				mapColliders << col;
			} else {
				actColliders << col;
			}
		}

		auto check = [this, &prevCollision](const Ref<Actor::ICollider>& it1, const Ref<Actor::ICollider>& it2) {
			CollisionPairHash hash(it1->getId(), it2->getId());
			if (ColisionUtil::Intersects(it1->getCollider(), it2->getCollider())) {
				m_currentCollision.insert(hash);
				if (prevCollision.find(hash) == prevCollision.end()) {
					// onEnter
					it1->onCollisionEnter(it2.get());
					it2->onCollisionEnter(it1.get());
				}
				// onStay
				it1->onCollisionStay(it2.get());
				it2->onCollisionStay(it1.get());
			} else {
				if (prevCollision.find(hash) != prevCollision.end()) {
					// onExit
					it1->onCollisionExit(it2.get());
					it2->onCollisionExit(it1.get());
				}
			}
		};
		// キャラvs地形の当たり
		for (auto&& col1 : actColliders) {
			for (auto&& col2 : mapColliders) {
				check(col1, col2);
			}
		}

		// キャラ等の相互当たり
		for (auto it1 = actColliders.begin(); it1 != actColliders.end(); ++it1) {
			for (auto it2 = it1 + 1; it2 != actColliders.end(); ++it2) {
				if ((*it1)->getLayer() == (*it2)->getLayer()) {
					continue;
				}
				check((*it1), (*it2));
			}
		}

	}
	void SimpleCollision::reset()
	{
		m_currentCollision.clear();
	}
}

