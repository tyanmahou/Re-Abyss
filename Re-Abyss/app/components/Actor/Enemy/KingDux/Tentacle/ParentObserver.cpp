#include <abyss/components/Actor/Enemy/KingDux/Tentacle/ParentObserver.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	ParentObserver::ParentObserver(ActorObj* pActor, ActorObj* pParent):
		m_pActor(pActor),
		m_parentDeadChecker(pParent->find<DeadChecker>())
	{}
	void ParentObserver::onLastUpdate()
	{
		if (!m_parentDeadChecker || m_parentDeadChecker->isDead()) {
			m_pActor->destroy();
		}
	}
}
