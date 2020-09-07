#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Actor::Player
{
    class RoomMoveChecker :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        PlayerActor* m_pActor;
    public:
        RoomMoveChecker(PlayerActor* pActor);

        void setup() override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::RoomMoveChecker>
    {
        using Base = ILastUpdateModel;
    };
}