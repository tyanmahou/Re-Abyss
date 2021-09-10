#include "DistCtrl.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Distortion/Distortion.hpp>

#include <Siv3D.hpp>

namespace abyss::Effect::Misc::ShockWaveDist
{
    DistCtrl::DistCtrl(EffectObj* pObj, const s3d::Vec2& pos, double radius, double power):
        m_pObj(pObj),
        m_pos(pos),
        m_radius(radius),
        m_power(power)
    {}
    bool DistCtrl::isEnd() const
    {
        return m_pObj->updateTimeSec() > 1.0;
    }
    void DistCtrl::onDraw(double time)
    {
        double rate = EaseOut(Easing::Quint, time);
        auto distortion = m_pObj->getModule<Distortion>();

        distortion->addCircleFrame(
            Circle(m_pos, m_radius * rate),
            10,
            10,
            0,
            s3d::Math::Lerp(0.0, m_power, s3d::Periodic::Triangle0_1(1s, rate))
        );
    }
}
