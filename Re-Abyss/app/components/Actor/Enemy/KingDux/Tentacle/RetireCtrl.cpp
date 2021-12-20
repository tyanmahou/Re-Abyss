#include "RetireCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	RetireCtrl::RetireCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void RetireCtrl::onStart()
	{
		m_body = m_pActor->find<Body>();
		m_rotCtrl = m_pActor->find<RotateCtrl>();
		m_colCtrl = m_pActor->find<ColCtrl>();
	}
	void RetireCtrl::onMove()
	{
		if (!m_isActive) {
			return;
		}
		m_speed += m_accel * m_pActor->deltaTime();
		if (m_speed > 0) {
			m_speed = 0;
		}
		m_body
			->setVelocity(m_speed * m_rotCtrl->getDir9());
	}
	void RetireCtrl::onPostCollision()
	{
		if (!m_isActive) {
			return;
		}

		s3d::int32 damage = 0;
		m_colCtrl->anyThen<Col::Attacker>([this, &damage](const Col::Attacker::Data& attacker) {
			damage += attacker.power;
			return true;
		});
		if (damage > 0) {
			m_speed = -s3d::Sqrt(2 * m_accel * damage * 30.0);
		}
	}
	void RetireCtrl::onStateStart()
	{
		m_isActive = false;
	}
}
