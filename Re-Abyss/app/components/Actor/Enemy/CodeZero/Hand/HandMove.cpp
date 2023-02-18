#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandMove.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/ShockWaveCtrl.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

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
        if (!m_isActive) {
            return;
        }
        m_task.resume();
    }
    void HandMove::onStateStart()
    {
        m_task.clear();
    }
    void HandMove::setActive(bool isActive)
    {
        m_isActive = isActive;
    }
    void HandMove::startAppear()
    {
        m_task.reset(std::bind(&HandMove::moveAppear, this));
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
    void HandMove::startForRollingAttack(bool isReverse)
    {
        m_task.reset(std::bind(&HandMove::moveRollingAttack, this, isReverse));
    }
    void HandMove::startAngry()
    {
        m_task.reset(std::bind(&HandMove::moveAngry, this));
    }
    void HandMove::startDeadFall()
    {
        m_task.reset(std::bind(&HandMove::moveDeadFall, this));
    }
    void HandMove::stop()
    {
        m_body->noneResistanced()
            .setVelocity(s3d::Vec2::Zero());
        m_task.clear();
        this->setActive(false);
    }
    bool HandMove::isMoveEnd() const
    {
        return m_task.isDone();
    }
    const Axis2& HandMove::getAxis() const
    {
        return m_param.axis;
    }
    Coro::Fiber<> HandMove::moveAppear()
    {
        Vec2 initPos = m_body->getPos();
        bool isLeft = m_pActor->find<KindCtrl>()->isLeftHand();
        TimeLite::Timer timer{ 3.0 };
        co_await Coro::Loop([&] {
            timer.update(m_pActor->deltaTime());
        m_body->setPos(initPos + Vec2{ 20 * (isLeft ? -1.0 : 1.0) ,20 } *timer.rate());
        });
    }
    Coro::Fiber<> HandMove::movePursuit(bool slowStart)
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
    Coro::Fiber<> HandMove::moveAttackWait()
    {
        auto velocity = m_param.axis.projectRight(-50);
        m_body->setVelocity(velocity);

        // 一定時間追従
        co_await BehaviorUtil::WaitForSeconds(m_parent->getParent(), HandParam::Attack::WaitTimeSec);

        co_return;
    }
    Coro::Fiber<> HandMove::moveAttack()
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
    Coro::Fiber<> HandMove::moveShotCharge()
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
    Coro::Fiber<> HandMove::moveRollingAttack(bool isReverse)
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
            const auto rate = moveTimer.rate();
            const auto rate2 = s3d::EaseInOutQuad(rate);

            auto rotate = s3d::ToRadians(s3d::Fmod((360 * 2 + 30) * rate2 * (isReverse ? -1.0 : 1.0), 360));
            auto newToHand = toHand.rotated(rotate);
            if (!newToHand.isZero()) {
                newToHand.normalize();
            }

            auto rotate2 = s3d::ToRadians(s3d::Fmod((360 * 2 + 15) * rate2 * (isReverse ? -1.0 : 1.0), 360));
            auto newAxis = toHand.rotated(rotate2);
            if (!newAxis.isZero()) {
                newAxis.normalize();
            }

            m_param.axis = Axis2::FromRight(-newAxis);

            auto newDist = s3d::Math::Lerp(dist, 500.0, rate2);
            m_param.distance = newDist;
            m_param.rotateLimit = rotate2;
            auto offset = Param::Head::Offset * rate;
            m_body->setPos(parentPos + offset + newDist * newToHand);
            m_rotate->setRotate(initRotate + rotate2);
            co_yield{};
        }
        co_return;
    }
    Coro::Fiber<> HandMove::moveAngry()
    {
        const Vec2 initVec = m_body->getVelocity()
            .limitLength(HandParam::Pursuit::Speed);
        TimeLite::Timer moveTimer(2.0);

        while (!moveTimer.isEnd()) {
            moveTimer.update(m_pActor->deltaTime());

            auto rate = moveTimer.rate();
            m_body->setVelocity(initVec * (1 - rate));
            co_yield{};
        }
        co_return;
    }
    Coro::Fiber<> HandMove::moveDeadFall()
    {
        bool isLeft = m_pActor->find<KindCtrl>()->isLeftHand();
        m_body->setAccelY(Body::DefaultGravity);
        m_body->setMaxVelocityY(Body::DefaultMaxVelocityY * 1.5);

        TimeLite::Timer slowTimer{ 2.0 };
        while (true)
        {
            auto dt = m_pActor->deltaTime();
            slowTimer.update(dt);

            auto dampRatio = InterpUtil::DampRatio(0.02 * slowTimer.rate(), dt);
            const double rotateEnd = isLeft ? Math::ToRadians(40 + 90) : Math::ToRadians(-40 - 90);
            m_rotate->setRotate(s3d::Math::Lerp( m_rotate->getRotate(), rotateEnd, dampRatio));
            co_yield{};
        }
        co_return;
    }
}
