#include "DamageModel.hpp"
#include <abyss/commons/ActInclude.hpp>

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
			if (m_hp->damage(attacker.getPower()) && m_hp->isDead()) {
				//m_pActor->destroy();
				//this->onDead();
			}
		});
    }

}
