#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Player
{
    class RoomMoveCheckerModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        Ref<BodyModel> m_body;
        IActor* m_pActor;
    public:
        RoomMoveCheckerModel(IActor* pActor);

        void setup() override;
        void onLastUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Player::RoomMoveCheckerModel>
    {
        using Base = ILastUpdateModel;
    };
}