#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Player
{
    class RoomMoveChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        ActorObj* m_pActor;
    public:
        RoomMoveChecker(ActorObj* pActor);

        void setup(Executer executer) override;

        void onStart() override;

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