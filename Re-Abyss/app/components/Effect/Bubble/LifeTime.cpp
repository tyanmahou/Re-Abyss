#include "LifeTime.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Bubble
{
    LifeTime::LifeTime(EffectObj* pObj):
        m_pObj(pObj)
    {}
    void LifeTime::onUpdate()
    {
        double dt = m_pObj->deltaTime();
        m_lifeTime -= dt;
        if (m_lifeTime <= 0) {
            m_lifeTime = 0;

            m_destroyTime -= dt;
        }
        if (m_destroyTime <= 0) {
            m_pObj->destroy();
        }
    }
    double LifeTime::destroyRate() const
    {
        return s3d::Saturate(m_destroyTime / m_destroyMax);
    }
}
