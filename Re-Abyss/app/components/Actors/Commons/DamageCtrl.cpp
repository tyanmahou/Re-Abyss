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
		if (m_pActor->isDestroyed()) {
			return;
		}
		const bool isDamaged = m_colCtrl->eachThen<Tag::Attacker, AttackerData>([this](const AttackerData& attacker) {
			return m_hp->damage(attacker.getPower());
		});
		if (isDamaged) {
			for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
				callback->onDamaged();
			}
		}
	}
}
