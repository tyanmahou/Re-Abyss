#include "DamageCtrl.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/components/Actors/base/IDamageCallback.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>

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
		col->getActor()->accept([this](const Attacker& attacker) {
			if (m_hp->damage(attacker.getPower())) {
				for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
					callback->onDamaged();
				}
			}
		});
    }

}
