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
	}
	void DamageCtrl::onCollisionStay(ICollider* col)
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		col->isThen<Tag::Attacker, AttackerData>([this](const AttackerData& attacker) {
			if (m_hp->damage(attacker.getPower())) {
				for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
					callback->onDamaged();
				}
			}
		});
    }

}
