#include "DamageCtrl.hpp"

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/base/IDamageCallback.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	DamageCtrl::DamageCtrl(IActor* pActor) :
		m_pActor(pActor)
	{}
	void DamageCtrl::onStart()
	{
		m_parent = m_pActor->find<ParentCtrl>();
		m_col = m_pActor->find<CollisionCtrl>();
	}
	void DamageCtrl::onCollisionReact()
	{
		auto parent = m_parent->getParent();
		auto hp = m_parent->getHp();
		if (!hp) {
			return;
		}
		const bool isDamaged = m_col->eachThen<Tag::Attacker, AttackerData>([=](const AttackerData& attacker) {
			return hp->damage(attacker.getPower());
		});
		if (isDamaged) {
			for (auto&& callback : parent->finds<IDamageCallback>()) {
				callback->onDamaged();
			}
		}
	}
}