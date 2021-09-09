#include "HandCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandCtrl::HandCtrl(const s3d::Vec2& dir, double rotateLimit):
        m_axis(Axis2::FromRight(dir.normalized())),
        m_rotateLimit(rotateLimit),
        m_distance(dir.length())
    {
    }
    void HandCtrl::updateRotate(RotateCtrl& rotate, double dt)const
    {
        bool isPlus = m_rotateLimit >= 0;
        double value = rotate.addRotate(isPlus ? dt : -dt).getRotate();
        if (isPlus && value >= m_rotateLimit || !isPlus && value <= m_rotateLimit) {
            rotate.setRotate(m_rotateLimit);
        }
    }
    void HandCtrl::startForPursuit(Body& body)const
    {
        auto velocity = m_axis * Vec2{ -HandParam::Setup::Speed, HandParam::Pursuit::Speed };
        body.setVelocity(velocity);
    }

    void HandCtrl::updateForPursuit(const s3d::Vec2& target, const s3d::Vec2& parentPos, Body& body, double dt)const
    {
        const auto& pos = body.getPos();
        Vec2 velocity{ 0,0 };

        {
            // 前方向の動き
            // 目的地に向かって進む
            Vec2 targetPos = parentPos - m_axis.projectRight(m_distance);
            targetPos += m_axis.projectDown(parentPos - pos);
            auto vec = (targetPos - pos);
            auto vecNormal = vec.normalized();
            double speed = HandParam::Setup::Speed;
            if (auto len = Abs(m_axis.relativeX(vec)); dt != 0.0 && len < speed * dt) {
                speed = len / dt;
            }
            velocity += m_axis.projectRight(vecNormal) * speed;
        }
        {
            // 横方向の動き
            const auto targetVec = target - pos;
            if (auto distance = m_axis.relativeY(targetVec); distance >= 60) {
                velocity += m_axis.projectDown(HandParam::Pursuit::Speed);
                body.setVelocity(velocity);
            } else if (distance <= -60) {
                velocity -= m_axis.projectDown(HandParam::Pursuit::Speed);
                body.setVelocity(velocity);
            } else {
                velocity += m_axis.projectDown(body.getVelocity());
                body.setVelocity(velocity);
            }
        }
    }

    void HandCtrl::startForAttackWait(Body& body)const
    {
        auto velocity = m_axis.projectRight(-50);
        body.setVelocity(velocity);
    }

    void HandCtrl::startForAttack(Body& body) const
    {
        auto velocity = m_axis.projectRight(HandParam::Attack::Speed);
        body.setVelocity(velocity);
    }

    bool HandCtrl::updateForAttack(
        bool& isReturn,
        const s3d::Vec2& parentPos,
        Body& body,
        double dt
    ) const{
        const auto& pos = body.getPos();
        const auto targetVec = parentPos - pos;
        bool ret = true;

        auto deltaVelocity = m_axis.relativeX(body.getVelocity()) * dt;
        if (auto distance = m_axis.relativeX(targetVec); !isReturn && distance <= -m_distance-40) {
            isReturn = true;
            auto velocity = m_axis.projectRight(-HandParam::Attack::Speed);
            body.setVelocity(velocity);
        } else if (isReturn && distance + deltaVelocity >= m_distance) {
            auto velocity = m_axis.projectRight(m_distance - distance);
            body.setVelocity(velocity);
            ret = false;
        }
        return ret;
    }

    HandCtrl HandCtrl::CreateLeftPhase1()
    {
        return HandCtrl(s3d::Vec2{-HandParam::Base::HorizontalDist, 0 }, Math::ToRadians(40));
    }

    HandCtrl HandCtrl::CreateRightPhase1()
    {
        return HandCtrl(s3d::Vec2{ 0, HandParam::Base::VerticalDist }, Math::ToRadians(50));
    }

    HandCtrl HandCtrl::CreateLeftPhase2()
    {
        return HandCtrl(s3d::Vec2{ 0, HandParam::Base::VerticalDist }, Math::ToRadians(-50));
    }

    HandCtrl HandCtrl::CreateRightPhase2()
    {
        return HandCtrl(s3d::Vec2{ HandParam::Base::HorizontalDist, 0 }, Math::ToRadians(-40));
    }

}
