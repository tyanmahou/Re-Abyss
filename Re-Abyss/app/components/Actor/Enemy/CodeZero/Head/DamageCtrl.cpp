#include "DamageCtrl.hpp"

#include <abyss/components/Actor/Common/AttackerData.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/ICollider.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	DamageCtrl::DamageCtrl(ActorObj* pActor) :
		m_pActor(pActor),
		m_invincibleTime(0.2)
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
		m_parent = m_pActor->find<ParentCtrl>();
		m_col = m_pActor->find<CollisionCtrl>();
	}
	void DamageCtrl::onPostCollision()
	{
		m_invincibleTime.update(m_pActor->deltaTime());

		auto parent = m_parent->getParent();
		auto hp = m_parent->getHp();
		if (!hp) {
			return;
		}
		if (this->isInInvincibleTime()) {
			// 無敵
			return;
		}
		DamageData data{};
		const bool isDamaged = m_col->anyThen<Tag::Attacker, AttackerData>([this, &data, &hp](const AttackerData& attacker) {
			bool ret = hp->damage(attacker.getPower());
			if (ret) {
				data.damage = attacker.getPower();
				data.pos = attacker.getPos();
				data.velocity = attacker.getVelocity();
			}
			return ret;
		});
		if (isDamaged) {
			m_invincibleTime.reset();
			for (auto&& callback : parent->finds<IDamageCallback>()) {
				callback->onDamaged(data);
			}
		}
	}
}