#include <abyss/components/Actor/Common/Col/Collider/BodyCollider.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Col
{
	BodyCollider::BodyCollider(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void BodyCollider::onStart()
	{
		m_body = m_pActor->find<Body>();
	}

	CShape BodyCollider::getCollider() const
	{
		return m_body->region();
	}

}
