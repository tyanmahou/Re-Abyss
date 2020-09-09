#include "MainUpdate.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sencer/ParentCtrl.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>

namespace abyss::Actor::Enemy::Slime::Sencer
{
	MainUpdate::MainUpdate(IActor* pActor):
		m_pActor(pActor)
	{}
	void MainUpdate::setup()
    {
        m_parentCtrl = m_pActor->find<ParentCtrl>();
        m_mapColl = m_pActor->find<MapCollider>();
        m_body = m_pActor->find<BodyModel>();
    }
    void MainUpdate::onUpdate([[maybe_unused]]double dt)
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
			m_body->setPos(m_parentCtrl->getPos() + s3d::Vec2{ -20, 20 });
		} else {
			m_body->setPos(m_parentCtrl->getPos() + s3d::Vec2{ 20, 20 });
		}
	}
}
