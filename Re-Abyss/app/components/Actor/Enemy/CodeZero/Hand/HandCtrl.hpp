#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Axis2/Axis2.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandCtrl : public IComponent
    {
        abyss::Axis2 m_axis;
        double m_distance = 0;
        double m_rotateLimit = 0;
    public:
        HandCtrl() = default;
        HandCtrl(const s3d::Vec2& dir, double rotateLimit);
        void updateRotate(RotateCtrl& rotate, double dt) const;
        void startForPursuit(Body& body) const;
        void updateForPursuit(
            const s3d::Vec2& target,
            const s3d::Vec2& parentPos,
            Body& body,
            double dt
        ) const;
        void startForAttackWait(Body& body) const;

        void startForAttack(Body& body) const;

        bool updateForAttack(
            bool& isReturn,
            const s3d::Vec2& parentPos,
            Body& body,
            double dt
        ) const;

        static HandCtrl CreateLeftPhase1();
        static HandCtrl CreateRightPhase1();
        static HandCtrl CreateLeftPhase2();
        static HandCtrl CreateRightPhase2();

    };
}