#include "FaceCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>

namespace abyss::Actor::Enemy::Schield
{
	void FaceCollider::onStart()
	{
		m_face = m_pActor->find<FaceCtrl>();
	}
	CShape FaceCollider::getCollider() const
	{
		if (m_face->isOnFace()) {
			return m_face->getCollider();
		}
		return s3d::none;
	}
	FaceCollider::FaceCollider(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
}
