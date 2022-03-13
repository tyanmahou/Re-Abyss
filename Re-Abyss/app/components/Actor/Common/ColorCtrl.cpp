#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ColorCtrl::ColorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void ColorCtrl::setup([[maybe_unused]]Executer executer)
    {
    }

    void ColorCtrl::onStart()
    {
        m_damageCtrl = m_pActor->find<DamageCtrl>();
    }

    void ColorCtrl::onPreDraw()
    {
        const double dt = m_pActor->deltaTime();
        m_colorAnimTimer.update(dt);

        auto time = m_pActor->getTimeSec();
        m_colorMul = s3d::Palette::White;
        m_colorAdd = ColorF(0, 0);

        if (m_damageCtrl) {
            m_colorMul *= ColorDef::OnDamage(m_damageCtrl->isInvincibleTime(), time);
            m_colorAdd += ColorDef::Invincible(m_damageCtrl->isInvincibleState(), m_colorAnimTimer.current(), m_colorAnimTimer.rate());
        }
    }
    const s3d::ColorF& ColorCtrl::colorMul() const
    {
        return m_colorMul;
    }

    const s3d::ColorF& ColorCtrl::colorAdd() const
    {
        return m_colorAdd;
    }
}
