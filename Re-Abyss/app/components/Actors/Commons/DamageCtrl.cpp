#include "DamageCtrl.hpp"
#include <abyss/components/Actors/base/IDamageCallback.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>

namespace abyss::Actor
{
	DamageCtrl::DamageCtrl(IActor* pActor):
		m_pActor(pActor)
	{}
	void DamageCtrl::onStart()
	{
		m_hp = m_pActor->find<HP>();
		m_colCtrl = m_pActor->find<CollisionCtrl>();
	}
	void DamageCtrl::onPostCollision()
	{
		if (!m_isActive) {
			return;
		}
		if (m_pActor->isDestroyed()) {
			return;
		}
		DamageData data{};
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
			for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
				callback->onDamaged(data);
			}
		}
	}
}
