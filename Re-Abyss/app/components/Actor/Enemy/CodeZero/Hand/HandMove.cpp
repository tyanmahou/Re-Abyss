#include "HandMove.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
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
    
    }
    void HandMove::onStateStart()
    {
    
    }
    void HandMove::updateRotate() const
    {
        double dt = m_pActor->deltaTime();

        bool isPlus = m_param.rotateLimit >= 0;
        double value = m_rotate->addRotate(isPlus ? dt : -dt).getRotate();
        if (isPlus && value >= m_param.rotateLimit || !isPlus && value <= m_param.rotateLimit) {
            m_rotate->setRotate(m_param.rotateLimit);
        }
    }
    void HandMove::startForPursuit() const
    {
        auto velocity = m_param.axis * Vec2{ -HandParam::Setup::Speed, HandParam::Pursuit::Speed };
        m_body->setVelocity(velocity);
    }
    void HandMove::updateForPursuit() const
    {
        double dt = m_pActor->deltaTime();

        const auto& target = ActorUtils::PlayerPos(*m_pActor);
        const Vec2 parentPos = m_parent->getPos();
        const auto& pos = m_body->getPos();
        Vec2 velocity{ 0,0 };

        {
            // 前方向の動き
            // 目的地に向かって進む
            Vec2 targetPos = parentPos - m_param.axis.projectRight(m_param.distance);
            targetPos += m_param.axis.projectDown(parentPos - pos);
            auto vec = (targetPos - pos);
            auto vecNormal = vec.normalized();
            double speed = HandParam::Setup::Speed;
            if (auto len = Abs(m_param.axis.relativeX(vec)); dt != 0.0 && len < speed * dt) {
                speed = len / dt;
            }
            velocity += m_param.axis.projectRight(vecNormal) * speed;
        }
        {
            // 横方向の動き
            const auto targetVec = target - pos;
            if (auto distance = m_param.axis.relativeY(targetVec); distance >= 60) {
                velocity += m_param.axis.projectDown(HandParam::Pursuit::Speed);
                m_body->setVelocity(velocity);
            } else if (distance <= -60) {
                velocity -= m_param.axis.projectDown(HandParam::Pursuit::Speed);
                m_body->setVelocity(velocity);
            } else {
                velocity += m_param.axis.projectDown(m_body->getVelocity());
                m_body->setVelocity(velocity);
            }
        }
    }
    void HandMove::startForAttackWait() const
    {
        auto velocity = m_param.axis.projectRight(-50);
        m_body->setVelocity(velocity);
    }
    void HandMove::startForAttack()
    {
        auto velocity = m_param.axis.projectRight(HandParam::Attack::Speed);
        m_body->setVelocity(velocity);
        m_isReturn = false;
    }
    bool HandMove::updateForAttack()
    {
        const auto& pos = m_body->getPos();
        const Vec2 parentPos = m_parent->getPos();
        const auto targetVec = parentPos - pos;
        bool ret = true;
        double dt = m_pActor->deltaTime();
        auto deltaVelocity = m_param.axis.relativeX(m_body->getVelocity()) * dt;
        if (auto distance = m_param.axis.relativeX(targetVec); !m_isReturn && distance <= -m_param.distance - 40) {
            m_isReturn = true;
            auto velocity = m_param.axis.projectRight(-HandParam::Attack::Speed);
            m_body->setVelocity(velocity);
        } else if (m_isReturn && distance + deltaVelocity >= m_param.distance) {
            auto velocity = m_param.axis.projectRight(m_param.distance - distance);
            m_body->setVelocity(velocity);
            ret = false;
        }
        return ret;
    }
}
