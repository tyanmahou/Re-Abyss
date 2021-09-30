#include "DamageCtrl.hpp"
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/ICollider.hpp>
#include <abyss/components/Actor/Common/AttackerData.hpp>

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
		m_colCtrl = m_pActor->find<CollisionCtrl>();
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
		const bool isDamaged = m_colCtrl->anyThen<Tag::Attacker, AttackerData>([this, &data](const AttackerData& attacker) {
			bool ret = m_hp->damage(attacker.getPower());
			if (ret) {
				data.damage = attacker.getPower();
				data.pos = attacker.getPos();
				data.velocity = attacker.getVelocity();
			}
			return ret;
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
