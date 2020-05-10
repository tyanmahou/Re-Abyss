#include "DamageModel.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>
namespace abyss
{
	DamageModel::DamageModel(IActor* pActor):
		m_pActor(pActor)
	{}
	void DamageModel::setup()
	{
		m_hp = m_pActor->findComponent<experimental::HPModel>();
	}
	void DamageModel::onCollisionStay(IActor* col)
    {
		col->accept([this](const Attacker& attacker) {
			if (m_hp->damage(attacker.getPower())) {
				for (auto&& callback : m_pActor->findComponents<IDamageCallbackModel>()) {
					callback->onDamaged();
				}
				if (m_hp->isDead()) {
					for (auto&& callback : m_pActor->findComponents<IDeadCallbackModel>()) {
						callback->onDead();
					}
				}
			}
		});
    }

}
