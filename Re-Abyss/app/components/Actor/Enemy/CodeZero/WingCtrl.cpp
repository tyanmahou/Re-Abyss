#include <abyss/components/Actor/Enemy/CodeZero/WingCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    WingCtrl::WingCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {
    }
    void WingCtrl::setup(Executer executer)
    {
        executer.on<ILastUpdate>().addAfter<HeadCtrl>();
    }
    void WingCtrl::onStart()
    {
    }
    void WingCtrl::onLastUpdate()
    {
        double dt = m_pActor->deltaTime();
        if (dt <= 0) {
            // 更新不要
            return;
        }
        m_elapsedTimeSec += dt;
        auto fuwaFuwaOffset0_1 = s3d::Periodic::Sine0_1(Param::Wing::FuwaFuwaPeriod, m_elapsedTimeSec);
        m_localTargetL = Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1;
        m_localTargetR = Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1 * Vec2{-1, 1};
        auto dampRate = InterpUtil::DampRatio(Param::Wing::ErpRate, dt, 120_fps);
        m_localL = s3d::Math::Lerp(m_localL, m_localTargetL, dampRate);
        m_localR = s3d::Math::Lerp(m_localR, m_localTargetR, dampRate);
    }
}

