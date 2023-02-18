#include <abyss/components/Actor/Enemy/BossHpBarTarget.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy
{
    BossHpBarTarget::BossHpBarTarget(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void BossHpBarTarget::onStart()
    {
        m_hp = m_pActor->find<HP>();
        m_damageCtrl = m_pActor->find<DamageCtrl>();
    }
}
