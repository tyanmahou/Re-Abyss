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
		m_hp = m_pActor->find<HPModel>();
	}
	DamageModel& DamageModel::setAutoDestroy(bool isAuto)
	{
		m_isAutoDestroy = isAuto;
		return *this;
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
				if (m_hp->isDead()) {
					for (auto&& callback : m_pActor->finds<IDeadCallbackModel>()) {
						callback->onDead();
					}
					if (m_isAutoDestroy) {
						m_pActor->destroy();
					}
				}
			}
		});
    }

}
