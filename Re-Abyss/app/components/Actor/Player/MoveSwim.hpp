#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IMove.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>

namespace abyss::Actor::Player
{
    class MoveSwim :
        public IComponent,
        public IMove,
        public IStateCallback
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<Foot> m_foot;

        bool m_isActive = false;
    public:
        MoveSwim(ActorObj* pActor);

        void setup(Executer executer) override;

        void onStart() override;
        void onMove() override;

        void onStateStart() override;

        MoveSwim& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::MoveSwim>
    {
        using Base = MultiComponents<
            Actor::IMove,
            Actor::IStateCallback
        >;
    };
}