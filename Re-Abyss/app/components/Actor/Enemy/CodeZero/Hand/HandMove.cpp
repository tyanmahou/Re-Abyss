#include "HandMove.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/ShockWaveCtrl.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandMove::HandMove(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void HandMove::setup(Executer executer)
    {
        executer.on<IMove>().addBefore<BodyUpdater>();
    }
    void HandMove::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_rotate = m_pActor->find<RotateCtrl>();
        m_parent = m_pActor->find<ParentCtrl>();
    }
    void HandMove::onMove()
    {
        m_task.moveNext();
    }
    void HandMove::onStateStart()
    {
        m_task.clear();
    }
    void HandMove::startForPursuit(bool slowStart)
    {
        m_task.reset(std::bind(&HandMove::movePursuit, this, slowStart));
    }
    void HandMove::startForAttackWait()
    {
        m_task.reset(std::bind(&HandMove::moveAttackWait, this));
    }
    void HandMove::startForAttack()
    {
        m_task.reset(std::bind(&HandMove::moveAttack, this));
    }
    void HandMove::startForShotCharge()
    {
        m_task.reset(std::bind(&HandMove::moveShotCharge, this));
    }
    void HandMove::startForRollingAttack()
    {
        m_task.reset(std::bind(&HandMove::moveRollingAttack, this));
    }
    bool HandMove::isMoveEnd() const
    {
        return m_task.isDone();
    }
    const Axis2& HandMove::getAxis() const
    {
        return m_param.axis;
    }
    Coro::Task<> HandMove::movePursuit(bool slowStart)
    {
        const Vec2& target = ActorUtils::PlayerPos(*m_pActor);
        const Vec2& parentPos = m_parent->getPos();
        const Vec2& pos = m_body->getPos();

        {
            auto velocity = m_param.axis * Vec2{ -HandParam::Setup::Speed, HandParam::Pursuit::Speed };
            m_body->setVelocity(velocity);
        }

        TimeLite::Timer slowTimer(1.5);
        if (!slowStart) {
            slowTimer.toEnd();
        }
        while (true) {
            double dt = m_pActor->deltaTime();

            // スロウスタート
            double timeScale = 1.0;
            slowTimer.update(dt);
            if (!slowTimer.isEnd()) {
                auto timeRate = slowTimer.rate();
                timeScale *= (timeRate * timeRate);
            }

            // 回転
            {
                bool isPlus = m_param.rotateLimit >= 0;
                double value = m_rotate->addRotate((isPlus ? dt : -dt) * timeScale).getRotate();
                if (isPlus && value >= m_param.rotateLimit || !isPlus && value <= m_param.rotateLimit) {
                    m_rotate->setRotate(m_param.rotateLimit);
                }
            }

            // 速度更新
            Vec2 velocity{ 0,0 };
            {
                // 前方向の動き
                // 目的地に向かって進む
                Vec2 targetPos = parentPos - m_param.axis.projectRight(m_param.distance);
                targetPos += m_param.axis.projectDown(parentPos - pos);
                auto vec = (targetPos - pos);
                auto vecNormal = vec.normalized();
                double speed = HandParam::Setup::Speed * timeScale;
                if (auto len = Abs(m_param.axis.relativeX(vec)); dt != 0.0 && len < speed * dt) {
                    speed = len / dt;
                }
                velocity += m_param.axis.projectRight(vecNormal) * speed;
            }
            {
                // 横方向の動き
                const auto targetVec = target - pos;
                auto speed = HandParam::Pursuit::Speed * timeScale;

                if (auto distance = m_param.axis.relativeY(targetVec); distance >= 60) {
                    velocity += m_param.axis.projectDown(speed);
                    m_body->setVelocity(velocity);
                } else if (distance <= -60) {
                    velocity -= m_param.axis.projectDown(speed);
                    m_body->setVelocity(velocity);
                } else {
                    auto base = m_param.axis.projectDown(m_body->getVelocity());
                    base.setLength(speed);
                    velocity += base;
                    m_body->setVelocity(velocity);
                }
            }
            co_yield{};
        }
        co_return;
    }
    Coro::Task<> HandMove::moveAttackWait()
    {
        auto velocity = m_param.axis.projectRight(-50);
        m_body->setVelocity(velocity);

        // 一定時間追従
        co_yield BehaviorUtils::WaitForSeconds(m_parent->getParent(), HandParam::Attack::WaitTimeSec);

        co_return;
    }
    Coro::Task<> HandMove::moveAttack()
    {
        const Vec2& pos = m_body->getPos();
        const Vec2& parentPos = m_parent->getPos();

        // 初速
        {
            auto velocity = m_param.axis.projectRight(HandParam::Attack::Speed);
            m_body->setVelocity(velocity);
        }

        // 攻撃
        m_pActor->find<ShockWaveCtrl>()->setActive(true);
        while (true) {
            const auto targetVec = parentPos - pos;
            if (auto distance = m_param.axis.relativeX(targetVec); distance <= -m_param.distance - 40) {
                auto velocity = m_param.axis.projectRight(-HandParam::Attack::Speed);
                m_body->setVelocity(velocity);
                break;
            } else {
                co_yield{};
            }
        }
        m_pActor->find<ShockWaveCtrl>()->setActive(false);
        co_yield{};

        // 戻り
        while (true) {
            const auto targetVec = parentPos - pos;
            double dt = m_pActor->deltaTime();
            auto deltaVelocity = m_param.axis.relativeX(m_body->getVelocity()) * dt;
            if (auto distance = m_param.axis.relativeX(targetVec); distance + deltaVelocity >= m_param.distance) {
                auto velocity = m_param.axis.projectRight(m_param.distance - distance);
                m_body->setVelocity(velocity);
                break;
            } else {
                co_yield{};
            }
        }
        co_return;
    }
    Coro::Task<> HandMove::moveShotCharge()
    {
        m_body->noneResistanced()
            .setVelocity(s3d::Vec2::Zero());

        bool isLeft = m_pActor->find<KindCtrl>()->isLeftHand();
        const Vec2& parentPos = m_parent->getPos();
        while (true) {
            auto dt = m_pActor->deltaTime();

            const s3d::Vec2 target = isLeft ?
                parentPos + s3d::Vec2{ 110, 0 } :
                parentPos + s3d::Vec2{ -110, 0 };
            auto dampRatio = InterpUtil::DampRatio(0.02, dt);
            m_body->setPos(m_body->getPos().lerp(target, dampRatio));

            const double rotateEnd = isLeft ? Math::ToRadians(40) : Math::ToRadians(-40);
            m_rotate->setRotate(s3d::EaseIn(s3d::Easing::Linear, m_rotate->getRotate(), rotateEnd, dampRatio));

            co_yield{};
        }
        co_return;
    }
    Coro::Task<> HandMove::moveRollingAttack()
    {
        m_body->noneResistanced()
            .setVelocity(s3d::Vec2::Zero());

        TimeLite::Timer moveTimer(3.5);
        const Vec2& parentPos = m_parent->getPos();
        const auto toHand = m_body->getPos() - parentPos;
        const auto dist = toHand.length();
        const auto initRotate = m_rotate->getRotate();
        while (!moveTimer.isEnd()) {
            moveTimer.update(m_pActor->deltaTime());
            auto rate = s3d::EaseInOutCubic(moveTimer.rate());

            auto rotate = s3d::ToRadians(s3d::Fmod(730 * rate, 360));
            auto newToHand = toHand.rotated(rotate);
            if (!newToHand.isZero()) {
                newToHand.normalize();
            }
            m_param.axis = Axis2::FromRight(-newToHand);

            auto newDist = s3d::Math::Lerp(dist, 500.0, rate);
            m_param.distance = newDist;
            m_param.rotateLimit = rotate;
            m_body->setPos(parentPos + newDist * newToHand);
            m_rotate->setRotate(initRotate + rotate);
            co_yield{};
        }
        co_return;
    }
}
