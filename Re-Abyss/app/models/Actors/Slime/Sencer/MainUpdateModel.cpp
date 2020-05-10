#include "MainUpdateModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Slime/Sencer/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Slime/Sencer/CollisionModel.hpp>
#include <abyss/models/Actors/Commons/PosModel.hpp>

namespace abyss::Slime::Sencer
{
	MainUpdateModel::MainUpdateModel(IActor* pActor):
		m_pActor(pActor)
	{}
	void MainUpdateModel::setup()
    {
        m_parentCtrl = m_pActor->find<ParentCtrlModel>();
        m_collision = m_pActor->find<CollisionModel>();
        m_pos = m_pActor->find<PosModel>();
    }
    void MainUpdateModel::onUpdate([[maybe_unused]]double dt)
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (!m_collision->isOnCollision() && m_parentCtrl->isWalk()) {
			m_parentCtrl->reversed();
		}
		auto isLeft = m_parentCtrl->getForward() == Forward::Left;
		if (isLeft) {
			m_pos->setPos(m_parentCtrl->getPos() + s3d::Vec2{ -20, 20 });
		} else {
			m_pos->setPos(m_parentCtrl->getPos() + s3d::Vec2{ 20, 20 });
		}
    }
}
