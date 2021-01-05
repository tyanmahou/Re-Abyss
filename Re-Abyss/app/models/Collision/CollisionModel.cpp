#include "CollisionModel.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>
#include <abyss/components/Actors/base/ICollision.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

namespace abyss
{
	void SimpleCollision::collisionAll(const s3d::Array<Ref<Actor::ICollision>>& collisions)
	{
		// Collision
		using Actor::ICollision;

		s3d::Array<Ref<ICollision>> actColliders;
		actColliders.reserve(collisions.size());
		s3d::Array<Ref<ICollision>> mapColliders;
		mapColliders.reserve(collisions.size());

		for (const auto& col : collisions) {
			if (!col || !col->isActive()) {
				continue;
			}
			if (col->getLayer() == LayerGroup::Map) {
				mapColliders << col;
			} else {
				actColliders << col;
			}
		}

		auto check = [this](const Ref<ICollision>& it1, const Ref<ICollision>& it2) {
			if (it1->getId() == it2->getId()) {
				// 同一アクターなら無視
				return;
			}
			if (ColisionUtil::Intersects(it1->getCollider(), it2->getCollider())) {

				// onCollision
				it1->onCollision(it2);
				it2->onCollision(it1);
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

				if (((*it1)->getLayer() & (*it2)->getToLayer()) != 0 && 
					((*it1)->getToLayer() & (*it2)->getLayer()) != 0
				) {
					continue;
				}
				check((*it1), (*it2));
			}
		}

	}
	void SimpleCollision::reset()
	{
	}
}

