#include <abyss/components/Actor/Enemy/BabyDux/ParentObserver.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	ParentObserver::ParentObserver(ActorObj* pActor, ActorObj* pParent):
		m_pActor(pActor),
		m_parentDeadChecker(pParent->find<DeadChecker>())
	{}
	void ParentObserver::onStart()
	{
		m_deadChecker = m_pActor->find<DeadChecker>();
	}
	void ParentObserver::onLastUpdate()
	{
		if (!m_parentDeadChecker || m_parentDeadChecker->isDead()) {
			if (m_deadChecker) {
				m_deadChecker->requestDead();
			} else {
				m_pActor->destroy();
			}
		}
	}
}
