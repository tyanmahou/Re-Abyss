#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IStateCallback.hpp>

namespace abyss::Actor::Player
{
    class StateChecker :
        public IComponent,
        public IStateCallback
    {
    public:
        StateChecker(ActorObj* pActor);

        void onStateStart() override;

        StateChecker& setCanDoorState(bool canDoorState)
        {
            m_canDoorState = canDoorState;
            return *this;
        }
        bool canDoorState() const
        {
            return m_canDoorState;
        }
    private:
        ActorObj* m_pActor = nullptr;

        bool m_canDoorState = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::StateChecker>
    {
        using Base = MultiComponents<
            Actor::IStateCallback
        >;
    };
}