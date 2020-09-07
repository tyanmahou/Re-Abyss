#include "DamageCtrl.hpp"

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	DamageCtrl::DamageCtrl(IActor* pActor) :
		m_pActor(pActor)
	{}
	void DamageCtrl::setup()
	{
		m_parent = m_pActor->find<ParentCtrl>();
	}
	void DamageCtrl::onCollisionStay(IActor* col)
	{
		auto parent = m_parent->getParent();
		auto hp = m_parent->getHp();
		if (!hp) {
			return;
		}
		col->accept([this, hp, parent](const Attacker& attacker) {
			if (hp->damage(attacker.getPower())) {
				for (auto&& callback : parent->finds<IDamageCallbackModel>()) {
					callback->onDamaged();
				}
			}
		});
	}
}