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
}
