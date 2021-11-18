#include "SimpleDetection.hpp"
#include <abyss/modules/Collision/base/INode.hpp>
#include <abyss/modules/Collision/LayerGroup.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Collision
{
	void SimpleDetection::collisionAll(const s3d::Array<std::shared_ptr<INode>>& nodes)
	{
		s3d::Array<std::shared_ptr<INode>> actColliders;
		actColliders.reserve(nodes.size());
		s3d::Array<std::shared_ptr<INode>> mapColliders;
		mapColliders.reserve(nodes.size());

		for (const auto& node : nodes) {
			if (!node || !node->isActive()) {
				continue;
			}
			if (node->layer() == LayerGroup::Map) {
				mapColliders << node;
			}
			else {
				actColliders << node;
			}
		}

		auto check = [this](const std::shared_ptr<INode>& it1, const std::shared_ptr<INode>& it2) {
			if (it1->id() == it2->id()) {
				// 同一アクターなら無視
				return;
			}
			if (ColisionUtil::Intersects(it1->getShape(), it2->getShape())) {

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

				if (((*it1)->layer() & (*it2)->toLayer()) == 0 || 
					((*it1)->toLayer() & (*it2)->layer()) == 0
				) {
					continue;
				}
				check((*it1), (*it2));
			}
		}
	}
}
