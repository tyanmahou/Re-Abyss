#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>

namespace abyss::Actor::Player
{
    class RoomMoveChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        PlayerActor* m_pActor;
    public:
        RoomMoveChecker(PlayerActor* pActor);

        void setup(Depends depends) override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::RoomMoveChecker>
    {
        using Base = Actor::ILastUpdate;
    };
}