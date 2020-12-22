#include "MainUpdate.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sensor/ParentCtrl.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
	MainUpdate::MainUpdate(IActor* pActor):
		m_pActor(pActor)
	{}
	void MainUpdate::onStart()
    {
        m_parentCtrl = m_pActor->find<ParentCtrl>();
        m_mapColl = m_pActor->find<MapCollider>();
        m_locator = m_pActor->find<Locator>();
    }
    void MainUpdate::onUpdate()
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (!m_mapColl->isHitAny() && m_parentCtrl->isWalk()) {
			m_parentCtrl->reversed();
		}
    }
	void MainUpdate::onPrePhysics()
	{
		auto isLeft = m_parentCtrl->getForward() == Forward::Left;
		if (isLeft) {
			m_locator->setPos(m_parentCtrl->getPos() + s3d::Vec2{ -20, 20 });
		} else {
			m_locator->setPos(m_parentCtrl->getPos() + s3d::Vec2{ 20, 20 });
		}
	}
}