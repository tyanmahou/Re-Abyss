#include "CodeZeroHandModel.hpp"
#include <Siv3D.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

namespace abyss
{
    CodeZeroHandModel::CodeZeroHandModel(const s3d::Vec2& dir, double rotateLimit):
        m_dir(dir.normalized()),
        m_dirVertical(m_dir.y, -m_dir.x),
        m_rotateLimit(rotateLimit),
        m_distance(dir.length())
    {
    }
    void CodeZeroHandModel::updateRotate(RotateModel& rotate, double dt)const
    {
        bool isPlus = m_rotateLimit >= 0;
        double value = rotate.addRotate(isPlus ? dt : -dt).getRotate();
        if (isPlus && value >= m_rotateLimit || !isPlus && value <= m_rotateLimit) {
            rotate.setRotate(m_rotateLimit);
        }
    }
    void CodeZeroHandModel::startForPursuit(BodyModel& body)const
    {
        auto velocity =
            m_dir * -CodeZeroParam::Hand::SetUpSpeed
            + m_dirVertical * CodeZeroParam::Hand::PursuitSpeed;
        body.setVelocity(velocity);
    }

    void CodeZeroHandModel::updateForPursuit(const s3d::Vec2& target, const s3d::Vec2& parentPos, BodyModel& body, double dt)const
    {
        const auto& pos = body.getPos();
        auto velocity = m_dir * -CodeZeroParam::Hand::SetUpSpeed;

        {
            const auto targetVec = target - pos;
            if (auto distance = m_dirVertical.dot(targetVec); distance >= 60) {
                velocity += m_dirVertical * CodeZeroParam::Hand::PursuitSpeed;
                body.setVelocity(velocity);
            } else if (distance <= -60) {
                velocity -= m_dirVertical * CodeZeroParam::Hand::PursuitSpeed;
                body.setVelocity(velocity);
            }
        }

        body.update(dt);

        {
            double border = m_distance;
            const auto targetVec = parentPos - pos;
            if (auto distance = m_dir.dot(targetVec); distance >= border) {
                body.setPos(pos + m_dir * (distance - border));
            }
        }
    }

    void CodeZeroHandModel::startForAttackWait(BodyModel& body)const
    {
        auto velocity = m_dir * -50;
        body.setVelocity(velocity);
    }

    void CodeZeroHandModel::startForAttack(BodyModel& body) const
    {
        auto velocity = m_dir * CodeZeroParam::Hand::AttackSpeed;
        body.setVelocity(velocity);
    }

    void CodeZeroHandModel::updateForAttack(
        bool& isReturn,
        const s3d::Vec2& parentPos,
        BodyModel& body,
        double dt,
        std::function<void()> callback
    ) const{
        const auto& pos = body.getPos();
        const auto targetVec = parentPos - pos;
        if (auto distance = m_dir.dot(targetVec); !isReturn && distance <= -m_distance-40) {
            isReturn = true;
            auto velocity = m_dir * -CodeZeroParam::Hand::AttackSpeed;
            body.setVelocity(velocity);
        } else if (isReturn && distance >= m_distance) {
            body.setPos(pos + m_dir * (distance - m_distance));
            callback();
        }
        body.update(dt);
    }

    CodeZeroHandModel CodeZeroHandModel::CreateLeftPhase1()
    {
        return CodeZeroHandModel(s3d::Vec2{-400, 0 }, Math::ToRadians(40));
    }

    CodeZeroHandModel CodeZeroHandModel::CreateRightPhase1()
    {
        return CodeZeroHandModel(s3d::Vec2{ 0, 250 }, Math::ToRadians(50));
    }

    CodeZeroHandModel CodeZeroHandModel::CreateLeftPhase2()
    {
        return CodeZeroHandModel(s3d::Vec2{ 0, 250 }, Math::ToRadians(-50));
    }

    CodeZeroHandModel CodeZeroHandModel::CreateRightPhase2()
    {
        return CodeZeroHandModel(s3d::Vec2{ 400, 0 }, Math::ToRadians(-40));
    }

}
