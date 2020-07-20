#include "DamageModel.hpp"

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>

#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>

namespace abyss::CodeZero::Head
{
	DamageModel::DamageModel(IActor* pActor) :
		m_pActor(pActor)
	{}
	void DamageModel::setup()
	{
		m_parent = m_pActor->find<ParentCtrlModel>();
	}
	void DamageModel::onCollisionStay(IActor* col)
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