#include "DamageCtrl.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/components/Actors/base/IDamageCallback.hpp>
namespace abyss::Actor
{
	DamageCtrl::DamageCtrl(IActor* pActor):
		m_pActor(pActor)
	{}
	void DamageCtrl::setup()
	{
		m_hp = m_pActor->find<HP>();
	}
	void DamageCtrl::onCollisionStay(IActor* col)
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		col->accept([this](const Attacker& attacker) {
			if (m_hp->damage(attacker.getPower())) {
				for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
					callback->onDamaged();
				}
			}
		});
    }

}
