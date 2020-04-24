#pragma once
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::CodeZero
{
    class CodeZeroHandModel
    {
        s3d::Vec2 m_dir{};
        s3d::Vec2 m_dirVertical{};
        double m_distance = 0;
        double m_rotateLimit = 0;
    public:
        CodeZeroHandModel() = default;
        CodeZeroHandModel(const s3d::Vec2& dir, double rotateLimit);
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

        void updateForAttack(
            bool& isReturn,
            const s3d::Vec2& parentPos,
            BodyModel& body,
            double dt,
            std::function<void()> callback
        ) const;

        static CodeZeroHandModel CreateLeftPhase1();
        static CodeZeroHandModel CreateRightPhase1();
        static CodeZeroHandModel CreateLeftPhase2();
        static CodeZeroHandModel CreateRightPhase2();

    };
}