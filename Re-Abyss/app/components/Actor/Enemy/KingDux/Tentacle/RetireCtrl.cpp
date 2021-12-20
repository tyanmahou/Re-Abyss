#include "RetireCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	RetireCtrl::RetireCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void RetireCtrl::onStart()
	{
		m_colCtrl = m_pActor->find<ColCtrl>();
	}
	void RetireCtrl::onMove()
	{

	}
	void RetireCtrl::onPostCollision()
	{

	}
	void RetireCtrl::onStateStart()
	{
		m_isActive = false;
	}
}
