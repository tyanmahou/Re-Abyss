#include "ColCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Collision/CollisionManager.hpp>

namespace abyss::Actor::Collision
{
	ColCtrl::ColCtrl(ActorObj* pActor):
		m_pActor(pActor),
		m_id(pActor->getModule<CollisionManager>()->createId())
	{}

	void ColCtrl::setup(Executer executer)
	{
	}
	void ColCtrl::onStart()
	{
	}
	void ColCtrl::onEnd()
	{
		for(auto&& branch : m_branch) {
			if (branch) {
				branch->destroy();
			}
		}
	}

	bool ColCtrl::isHitAny() const
	{
		return m_branch.any([](const Ref<abyss::Collision::Branch>& b) {
			return b && b->result().isHitAny();
		});
	}

	bool ColCtrl::isHitBy(std::type_index type) const
	{
		return m_branch.any([type](const Ref<abyss::Collision::Branch>& b) {
			return b && b->result().isHitBy(type);
		});
	}
}
