#pragma once
#include"BaseState.hpp"
#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>

namespace abyss::Actor::Player
{
    class DoorInState final : public BaseState
    {
    public:
        DoorInState(const Ref<Gimmick::Door::DoorProxy>& door);
    private:
        void start() override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
    private:
        Ref<Gimmick::Door::DoorProxy> m_door;
    };
}