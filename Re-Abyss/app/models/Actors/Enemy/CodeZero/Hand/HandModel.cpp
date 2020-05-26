#include "HandModel.hpp"
#include <Siv3D.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::CodeZero::Hand
{
    HandModel::HandModel(const s3d::Vec2& dir, double rotateLimit):
        m_axis(dir.normalized()),
        m_rotateLimit(rotateLimit),
        m_distance(dir.length())
    {
    }
    void HandModel::updateRotate(RotateModel& rotate, double dt)const
    {
        bool isPlus = m_rotateLimit >= 0;
        double value = rotate.addRotate(isPlus ? dt : -dt).getRotate();
        if (isPlus && value >= m_rotateLimit || !isPlus && value <= m_rotateLimit) {
            rotate.setRotate(m_rotateLimit);
        }
    }
    void HandModel::startForPursuit(BodyModel& body)const
    {
        auto velocity = m_axis * Vec2{ -HandParam::Setup::Speed, HandParam::Setup::Speed };
        body.setVelocity(velocity);
    }

    void HandModel::updateForPursuit(const s3d::Vec2& target, const s3d::Vec2& parentPos, BodyModel& body, double dt)const
    {
        const auto& pos = body.getPos();
        Vec2 velocity{ 0,0 };
        
        {
            // 前方向の動き
            // 目的地に向かって進む
            Vec2 targetPos = parentPos - m_axis.sa(m_distance);
            auto vec = (targetPos - pos).normalized();
            velocity += m_axis.sa(vec) * HandParam::Setup::Speed;
        }
        {
            // 横方向の動き
            const auto targetVec = target - pos;
            if (auto distance = m_axis.t(targetVec); distance >= 60) {
                velocity += m_axis.tb(HandParam::Pursuit::Speed);
                body.setVelocity(velocity);
            } else if (distance <= -60) {
                velocity -= m_axis.tb(HandParam::Pursuit::Speed);
                body.setVelocity(velocity);
            }
        }
        body.update(dt);
    }

    void HandModel::startForAttackWait(BodyModel& body)const
    {
        auto velocity = m_axis.sa(-50);
        body.setVelocity(velocity);
    }

    void HandModel::startForAttack(BodyModel& body) const
    {
        auto velocity = m_axis.sa(HandParam::Attack::Speed);
        body.setVelocity(velocity);
    }

    void HandModel::updateForAttack(
        bool& isReturn,
        const s3d::Vec2& parentPos,
        BodyModel& body,
        double dt,
        std::function<void()> callback
    ) const{
        const auto& pos = body.getPos();
        const auto targetVec = parentPos - pos;
        if (auto distance = m_axis.s(targetVec); !isReturn && distance <= -m_distance-40) {
            isReturn = true;
            auto velocity = m_axis.sa(-HandParam::Attack::Speed);
            body.setVelocity(velocity);
        } else if (isReturn && distance >= m_distance) {
            body.setPos(pos + m_axis.sa(distance - m_distance));
            callback();
        }
        body.update(dt);
    }

    HandModel HandModel::CreateLeftPhase1()
    {
        return HandModel(s3d::Vec2{-400, 0 }, Math::ToRadians(40));
    }

    HandModel HandModel::CreateRightPhase1()
    {
        return HandModel(s3d::Vec2{ 0, 250 }, Math::ToRadians(50));
    }

    HandModel HandModel::CreateLeftPhase2()
    {
        return HandModel(s3d::Vec2{ 0, 250 }, Math::ToRadians(-50));
    }

    HandModel HandModel::CreateRightPhase2()
    {
        return HandModel(s3d::Vec2{ 400, 0 }, Math::ToRadians(-40));
    }

}
