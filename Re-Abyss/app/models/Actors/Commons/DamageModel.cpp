#include "DamageModel.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
namespace abyss
{
	DamageModel::DamageModel(IActor* pActor):
		m_pActor(pActor)
	{}
	void DamageModel::setup()
	{
		m_hp = m_pActor->find<HPModel>();
	}
	void DamageModel::onCollisionStay(IActor* col)
    {
		if (m_pActor->isDestroyed()) {
			return;
		}
		col->accept([this](const Attacker& attacker) {
			if (m_hp->damage(attacker.getPower())) {
				for (auto&& callback : m_pActor->finds<IDamageCallbackModel>()) {
					callback->onDamaged();
				}
			}
		});
    }

}
