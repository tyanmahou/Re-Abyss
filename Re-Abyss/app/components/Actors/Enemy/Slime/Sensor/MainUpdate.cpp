#include "MainUpdate.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
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
        m_collider = m_pActor->find<PointCollider>();
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
			m_collider->setPos(m_parentCtrl->getPos() + s3d::Vec2{ -20, 20 });
		} else {
			m_collider->setPos(m_parentCtrl->getPos() + s3d::Vec2{ 20, 20 });
		}
	}
}
