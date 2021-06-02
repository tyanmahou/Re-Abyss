#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IStateCallback.hpp>

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

        StateChecker& setIsDeadState(bool isDeadState)
        {
            m_isDeadState = isDeadState;
            return *this;
        }
        bool isDeadState() const
        {
            return m_isDeadState;
        }
    private:
        ActorObj* m_pActor = nullptr;

        bool m_canDoorState = false;
        bool m_isDeadState = false;
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