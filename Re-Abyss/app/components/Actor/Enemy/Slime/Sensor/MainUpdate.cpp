#include "MainUpdate.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/Slime/Sensor/ParentCtrl.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
	MainUpdate::MainUpdate(ActorObj* pActor):
		m_pActor(pActor)
	{}
	void MainUpdate::setup(Executer executer)
	{
		executer.on<IPrePhysics>().addBefore<MapCollider>();
	}
	void MainUpdate::onStart()
    {
        m_parentCtrl = m_pActor->find<ParentCtrl>();
        m_mapColl = m_pActor->find<MapCollider>();
        m_locator = m_pActor->find<Locator>();
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
	void MainUpdate::onPostPhysics()
	{
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (!m_mapColl->isHitAny() && m_parentCtrl->isWalk()) {
			m_parentCtrl->reversed();
		}
	}
}
