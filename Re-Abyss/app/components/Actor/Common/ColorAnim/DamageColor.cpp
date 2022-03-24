#include <abyss/components/Actor/Common/ColorAnim/DamageColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::ColorAnim
{
    DamageColor::DamageColor(ActorObj* pActor):
        m_pActor(pActor)
    {}

    s3d::ColorF DamageColor::colorMul() const
    {
        return ColorDef::OnDamage(m_damageCtrl->isInvincibleTime(), m_pActor->getTimeSec());
    }
    void DamageColor::onStart()
    {
        m_damageCtrl = m_pActor->find<DamageCtrl>();
    }
}
