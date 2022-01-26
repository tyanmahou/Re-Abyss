#include <abyss/modules/ColSys/SimpleDetection.hpp>

#include <abyss/modules/ColSys/Branch.hpp>
#include <abyss/modules/ColSys/LayerGroup.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::ColSys
{
	void SimpleDetection::collisionAll(const s3d::Array<std::shared_ptr<Branch>>& branchs)
	{
		s3d::Array<std::shared_ptr<Branch>> actBranchs;
		actBranchs.reserve(branchs.size());
		s3d::Array<std::shared_ptr<Branch>> mapBranchs;
		mapBranchs.reserve(branchs.size());

		for (const auto& branch : branchs) {
			if (!branch || !branch->isActive()) {
				continue;
			}
			if (branch->layer() == LayerGroup::Map) {
				mapBranchs << branch;
			}
			else {
				actBranchs << branch;
			}
		}

		auto check = [this](const std::shared_ptr<Branch>& it1, const std::shared_ptr<Branch>& it2) {
			if (it1->id() == it2->id()) {
				// 同一アクターなら無視
				return;
			}
			if ((it1->layer() & it2->toLayer()) == 0 ||
				(it1->toLayer() & it2->layer()) == 0
				) {
				return;
			}
			if (it1->isCollision(*it2)) {

				// onCollision
				it1->onCollision(*it2);
				it2->onCollision(*it1);
			}
		};

		// キャラvs地形の当たり
		for (auto&& col1 : actBranchs) {
			for (auto&& col2 : mapBranchs) {
				check(col1, col2);
			}
		}

		// キャラ等の相互当たり
		for (auto it1 = actBranchs.begin(); it1 != actBranchs.end(); ++it1) {
			for (auto it2 = it1 + 1; it2 != actBranchs.end(); ++it2) {
				check(*it1, *it2);
			}
		}
	}
}
