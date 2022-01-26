#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ParentObserver.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	ParentObserver::ParentObserver(ActorObj* pActor, ActorObj* pParent):
		m_pActor(pActor),
		m_parent(pParent)
	{}
	void ParentObserver::onStart()
	{
		m_deadChecker = m_pActor->find<DeadChecker>();
	}
	void ParentObserver::onLastUpdate()
	{
		if (!m_parent.isValid()) {
			if (m_deadChecker) {
				m_deadChecker->requestDead();
			} else {
				m_pActor->destroy();
			}
		}
	}
}
