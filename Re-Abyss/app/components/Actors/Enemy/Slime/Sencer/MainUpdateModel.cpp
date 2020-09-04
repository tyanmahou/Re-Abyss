#include "MainUpdateModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sencer/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>

namespace abyss::Actor::Enemy::Slime::Sencer
{
	MainUpdateModel::MainUpdateModel(IActor* pActor):
		m_pActor(pActor)
	{}
	void MainUpdateModel::setup()
    {
        m_parentCtrl = m_pActor->find<ParentCtrlModel>();
        m_mapColl = m_pActor->find<MapColliderModel>();
        m_body = m_pActor->find<BodyModel>();
    }
    void MainUpdateModel::onUpdate([[maybe_unused]]double dt)
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (!m_mapColl->isHitAny() && m_parentCtrl->isWalk()) {
			m_parentCtrl->reversed();
		}
    }
	void MainUpdateModel::onPrePhysics()
	{
		auto isLeft = m_parentCtrl->getForward() == Forward::Left;
		if (isLeft) {
			m_body->setPos(m_parentCtrl->getPos() + s3d::Vec2{ -20, 20 });
		} else {
			m_body->setPos(m_parentCtrl->getPos() + s3d::Vec2{ 20, 20 });
		}
	}
}
