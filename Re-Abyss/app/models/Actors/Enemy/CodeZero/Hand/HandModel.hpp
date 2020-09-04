#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Axis2/Axis2.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandModel : public IComponent
    {
        abyss::Axis2 m_axis;
        double m_distance = 0;
        double m_rotateLimit = 0;
    public:
        HandModel() = default;
        HandModel(const s3d::Vec2& dir, double rotateLimit);
        void updateRotate(RotateModel& rotate, double dt) const;
        void startForPursuit(BodyModel& body) const;
        void updateForPursuit(
            const s3d::Vec2& target,
            const s3d::Vec2& parentPos,
            BodyModel& body,
            double dt
        ) const;
        void startForAttackWait(BodyModel& body) const;

        void startForAttack(BodyModel& body) const;

        bool updateForAttack(
            bool& isReturn,
            const s3d::Vec2& parentPos,
            BodyModel& body,
            double dt
        ) const;

        static HandModel CreateLeftPhase1();
        static HandModel CreateRightPhase1();
        static HandModel CreateLeftPhase2();
        static HandModel CreateRightPhase2();

    };
}