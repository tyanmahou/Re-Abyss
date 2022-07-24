#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>

namespace abyss::Actor::Player
{
    class DoorInMapMoveState final : public BaseState
    {
    public:
        static void Change(
            ActorObj* player,
            const Gimmick::Door::DoorData& door,
            const s3d::String& link
        );
    public:
        DoorInMapMoveState(
            const Gimmick::Door::DoorData& door,
            const s3d::String& link
        );
    private:
        void start() override;
        void end() override;
        void update()override;
    private:
        Gimmick::Door::DoorData m_door;
        s3d::String m_link;
    };
}

