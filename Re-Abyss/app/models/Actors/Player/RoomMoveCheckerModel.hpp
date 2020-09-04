#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Actor::Player
{
    class RoomMoveCheckerModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        PlayerActor* m_pActor;
    public:
        RoomMoveCheckerModel(PlayerActor* pActor);

        void setup() override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::RoomMoveCheckerModel>
    {
        using Base = ILastUpdateModel;
    };
}