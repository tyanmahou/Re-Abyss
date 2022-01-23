#include "ParentObserver.hpp"

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	ParentObserver::ParentObserver(ActorObj* pActor, ActorObj* pParent):
		m_pActor(pActor),
		m_parent(pParent)
	{}
	void ParentObserver::onLastUpdate()
	{
		if (!m_parent.isValid()) {
			m_pActor->destroy();
		}
	}
}
