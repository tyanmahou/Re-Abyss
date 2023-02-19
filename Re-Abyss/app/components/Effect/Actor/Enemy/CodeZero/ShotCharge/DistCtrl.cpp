#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/DistCtrl.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Distortion/Distortion.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    using namespace abyss::Actor::Enemy::CodeZero;

    DistCtrl::DistCtrl(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos)
    {
    }
    bool DistCtrl::onDraw(double time)
    {
        double rate = (1 - Periodic::Sawtooth0_1(1.0s, time));

        const double totalTime = ShotParam::Wait::ScaleTime + 1.3;
        // 歪み
        double timeRate = s3d::Min(time, totalTime) / totalTime;
        double distPowerRate = s3d::Periodic::Triangle0_1(1s, timeRate);
        distPowerRate = EaseOut(Easing::Quint, distPowerRate);

        double distRate = 1 - EaseOut(Easing::Quint, timeRate);
        m_pObj->getModule<Distortion>()->addCircleFrameGiza(
            Circle(m_pos, 1300 * distRate),
            0,
            0,
            600 * distRate,
            100 + (1 - distRate) * 600,
            15.0 * distPowerRate,
            30.0 * distPowerRate * rate,
            time / 3.0,
            1
        );
        return time <= totalTime;
    }
}
