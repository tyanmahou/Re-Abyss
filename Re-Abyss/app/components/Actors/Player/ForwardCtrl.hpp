#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IMove.hpp>
#include <abyss/components/Actors/base/IStateCallback.hpp>

namespace abyss::Actor::Player
{
    class ForwardCtrl :
        public IComponent,
        public IMove,
        public IStateCallback
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        bool m_isActive = false;
    public:
        ForwardCtrl(IActor* pActor);

        void setup(Executer executer) override;

        void onStart() override;
        void onMove() override;

        void onStateStart() override;

        ForwardCtrl& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::ForwardCtrl>
    {
        using Base = MultiComponents<
            Actor::IMove,
            Actor::IStateCallback
        >;
    };
}