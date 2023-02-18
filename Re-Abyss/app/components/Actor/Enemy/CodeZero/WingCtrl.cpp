#include <abyss/components/Actor/Enemy/CodeZero/WingCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <abyss/utils/Shake/SimpleShake.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    WingCtrl::WingCtrl(ActorObj* pActor) :
        m_pActor(pActor)
    {
        m_localL = m_localTargetL = Param::Wing::InitLocalPos * Vec2{ -1, 1 };
        m_localR = m_localTargetR = Param::Wing::InitLocalPos;
    }
    void WingCtrl::startAppear()
    {
        m_elapsedTimeSec = 0;
        m_task.reset(std::bind(&WingCtrl::stateAppear, this));
    }
    void WingCtrl::startWait()
    {
        m_elapsedTimeSec = 0;
        m_task.reset(std::bind(&WingCtrl::stateWait, this));
    }
    void WingCtrl::startShot()
    {
        m_elapsedTimeSec = 0;
        m_task.reset(std::bind(&WingCtrl::stateShot, this));
    }
    void WingCtrl::startDead()
    {
        m_elapsedTimeSec = 0;
        m_task.reset(std::bind(&WingCtrl::stateDead, this));
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
        m_task.resume();
    }
    Coro::Fiber<> WingCtrl::stateAppear()
    {
        auto initL = m_localL;
        auto initR = m_localR;
        m_localTargetL = Vec2{ 0, 0 };
        m_localTargetR = Vec2{ 0, 0 };
        auto moveV = [&]()->Coro::Fiber<> {
            return Coro::Loop([this] {
                auto dt = m_pActor->deltaTime();
                auto dampRatio = InterpUtil::DampRatio(0.1, dt);
                m_localL.y = s3d::Math::Lerp(m_localL.y, m_localTargetL.y, dampRatio);
                m_localR.y = s3d::Math::Lerp(m_localR.y, m_localTargetR.y, dampRatio);
            });
        }; 
        auto moveH = [&]()->Coro::Fiber<> {
            co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.6s);
            TimeLite::Timer timer{ 1.4 };
            while (!timer.isEnd())
            {
                timer.update(m_pActor->deltaTime());
                auto rate = s3d::EaseOutQuad(timer.rate());
                m_localL.x = s3d::Math::Lerp(initL.x, m_localTargetL.x, rate);
                m_localR.x = s3d::Math::Lerp(initR.x, m_localTargetR.x, rate);
                co_yield{};
            }
            co_return;
        };
        co_await (moveV() & moveH());
    }
    Coro::Fiber<> WingCtrl::stateWait()
    {
        return Coro::Loop([this] {
            double dt = m_pActor->deltaTime();
            if (dt <= 0) {
                // 更新不要
                return;
            }
            m_elapsedTimeSec += dt;
            
            // 向きにあわせてオフセット計算
            {
                const Look& look = m_head->getLook();
                m_localTargetL = m_localTargetR = Vec2{ 0, 0 };
            
                if (look.isLeft()) {
                    m_localTargetL.x = m_localTargetR.x = Param::Wing::LookOffset.x;
                    m_localTargetL.x *= Param::Wing::LookDiffRate;
                } else if (look.isRight()) {
                    m_localTargetL.x = m_localTargetR.x = -Param::Wing::LookOffset.x;
                    m_localTargetR.x *= Param::Wing::LookDiffRate;
                }
                if (look.isUp()) {
                    m_localTargetL.y = m_localTargetR.y = Param::Wing::LookOffset.y;
                } else if (look.isDown()) {
                    m_localTargetL.y = m_localTargetR.y = -Param::Wing::LookOffset.y;
                }
            }
            // ふわふわ処理
            {
                auto fuwaFuwaOffset0_1 = s3d::Periodic::Sine0_1(Param::Wing::FuwaFuwaPeriod, m_elapsedTimeSec);
                m_localTargetL += Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1;
                m_localTargetR += Param::Wing::FuwaFuwaOffset * fuwaFuwaOffset0_1 * Vec2{ -1, 1 };
            }
            auto dampRatio = InterpUtil::DampRatio(Param::Wing::ErpRate, dt, 120_fps);
            m_localL = m_localL.lerp(m_localTargetL, dampRatio);
            m_localR = m_localR.lerp(m_localTargetR, dampRatio);
        });
    }
    Coro::Fiber<> WingCtrl::stateShot()
    {
        m_localTargetL = Param::Wing::InitLocalPos * Vec2{ -1, 1 };
        m_localTargetR = Param::Wing::InitLocalPos;
        return Coro::Loop([this] {
            auto dt = m_pActor->deltaTime();
            auto dampRatio = InterpUtil::DampRatio(0.02, dt);

            m_localL = m_localL.lerp(m_localTargetL, dampRatio);
            m_localR = m_localR.lerp(m_localTargetR, dampRatio);
        });
    }
    Coro::Fiber<> WingCtrl::stateDead()
    {
        // フェード開始を待つ
        auto* bossFade = m_pActor->getModule<SpecialEffects>()->bossFade();
        co_await Coro::WaitUntil([bossFade] {return bossFade->isActive(); });

        auto wingUpdate = [this](Vec2& wingLocalPos, double waitSec)->Coro::Fiber<>{
            Vec2 initPos = wingLocalPos;
            Vec2 move{ 0,0 };
            co_await BehaviorUtil::WaitForSeconds(m_pActor, waitSec);
            // 揺れる
            Shake::SimpleShake shake;
            shake.request(5.0, 0.4);
            auto shakeUpdater = Coro::Loop([&] {
                shake.update(m_pActor->deltaTime());
            });
            auto mover = [&]()->Coro::Fiber<> {
                co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.65);
                shake.request(2.0, -1);
                co_await Coro::Loop([&] {
                    move.y += 100.0 * m_pActor->deltaTime();
                });
            };
            auto updater = Coro::Loop([&] {
                wingLocalPos = initPos + move + shake.getShakeOffset();
            });
            co_await (std::move(shakeUpdater) | mover() | std::move(updater));
        };
        co_await(wingUpdate(m_localL, 0.5) & wingUpdate(m_localR, 2.0));
    }
}

