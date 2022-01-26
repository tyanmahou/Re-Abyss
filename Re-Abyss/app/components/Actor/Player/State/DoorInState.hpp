#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>

namespace abyss::Actor::Player
{
    class DoorInState final : public BaseState
    {
    public:
        DoorInState(const Ref<Gimmick::Door::DoorProxy>& door);
    private:
        void start() override;
        void end() override;
        void update()override;
    private:
        Ref<Gimmick::Door::DoorProxy> m_door;
    };
}