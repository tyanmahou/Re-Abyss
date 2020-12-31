#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Player
{
    class RoomMoveChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        IActor* m_pActor;
    public:
        RoomMoveChecker(IActor* pActor);

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