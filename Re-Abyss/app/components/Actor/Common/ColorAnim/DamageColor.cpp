#include <abyss/components/Actor/Common/ColorAnim/DamageColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::ColorAnim
{
    DamageColor::DamageColor(ActorObj* pActor):
        m_pActor(pActor)
    {}

    s3d::ColorF DamageColor::colorMul() const
    {
        return s3d::ColorF();
    }
    void DamageColor::onStart()
    {
        m_damageCtrl = m_pActor->find<DamageCtrl>();
    }
}
