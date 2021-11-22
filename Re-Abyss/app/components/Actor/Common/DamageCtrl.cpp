#include "DamageCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/Collision/Extension/Attacker.hpp>

namespace abyss::Actor
{
	DamageCtrl::DamageCtrl(ActorObj* pActor):
		m_pActor(pActor),
		m_invincibleTime(1.0)
	{}
	DamageCtrl& DamageCtrl::setInvincibleTime(double invincibleTimeSec)
	{
		m_invincibleTime.reset(invincibleTimeSec);
		m_invincibleTime.toEnd();
		return *this;
	}
	bool DamageCtrl::isInInvincibleTime() const
	{
		return !m_invincibleTime.isEnd();
	}
	void DamageCtrl::onStart()
	{
		m_hp = m_pActor->find<HP>();
		m_colCtrl = m_pActor->find<Collision::ColCtrl>();
	}
	void DamageCtrl::onPostCollision()
	{
		m_invincibleTime.update(m_pActor->deltaTime());
		m_damageData = s3d::none;

		if (!m_isActive) {
			return;
		}
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (this->isInInvincibleTime()) {
			// 無敵
			return;
		}

		DamageData data;
		const bool isDamaged = m_colCtrl->anyThen<Collision::Attacker>([this, &data](const Collision::Attacker::Data& attacker) {
			if (m_hp->damage(attacker.power)) {
				data.damage = attacker.power;
				data.pos = attacker.pos;
				data.velocity = attacker.velocity;
				return true;
			}
			return false;
		});
		if (isDamaged) {
			m_damageData = data;
			m_invincibleTime.reset();
			for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
				callback->onDamaged(data);
			}
		}
	}
}
