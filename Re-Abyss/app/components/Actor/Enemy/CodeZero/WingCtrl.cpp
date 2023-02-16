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
        m_head = m_pActor->find<HeadCtrl>();
    }
    void WingCtrl::onLastUpdate()
    {
        double dt = m_pActor->deltaTime();
        if (dt <= 0) {
            // 更新不要
            return;
        }
        m_elapsedTimeSec += dt;

        // 向きにあわせてオフセット計算
        {
            const Look& look = m_head->getLook();
            m_localTargetL = m_localTargetR = Vec2{0, 0};

            if (look.isForward(Forward::Left)) {
                m_localTargetL.x = m_localTargetR.x = Param::Wing::LookOffset.x;
                m_localTargetL.x *= Param::Wing::LookDiffRate;
            } else if (look.isForward(Forward::Right)) {
                m_localTargetL.x = m_localTargetR.x = -Param::Wing::LookOffset.x;
                m_localTargetR.x *= Param::Wing::LookDiffRate;
            }
            if (look.isForward(Forward::Up)) {
                m_localTargetL.y = m_localTargetR.y = Param::Wing::LookOffset.y;
            } else if (look.isForward(Forward::Down)) {
                m_localTargetL.y = m_localTargetR.y = -Param::Wing::LookOffset.y;
            }
        }
        // ふわふわ処理
        {
            auto fuwaFuwaOffset0_1 = s3d::Periodic::Sine0_1(Param::Wing::FuwaFuwaPeriod, m_elapsedTimeSec);
            m_localTargetL += Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1;
            m_localTargetR += Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1 * Vec2{ -1, 1 };
        }
        auto dampRate = InterpUtil::DampRatio(Param::Wing::ErpRate, dt, 120_fps);
        m_localL = s3d::Math::Lerp(m_localL, m_localTargetL, dampRate);
        m_localR = s3d::Math::Lerp(m_localR, m_localTargetR, dampRate);
    }
}

