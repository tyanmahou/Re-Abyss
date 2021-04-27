#include "DamageCtrl.hpp"

#include <abyss/components/Actor/Commons/AttackerData.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/base/IDamageCallback.hpp>
#include <abyss/components/Actor/base/ICollider.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	DamageCtrl::DamageCtrl(ActorObj* pActor) :
		m_pActor(pActor)
	{}
	void DamageCtrl::onStart()
	{
		m_parent = m_pActor->find<ParentCtrl>();
		m_col = m_pActor->find<CollisionCtrl>();
	}
	void DamageCtrl::onPostCollision()
	{
		auto parent = m_parent->getParent();
		auto hp = m_parent->getHp();
		if (!hp) {
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
			for (auto&& callback : parent->finds<IDamageCallback>()) {
				callback->onDamaged(data);
			}
		}
	}
}