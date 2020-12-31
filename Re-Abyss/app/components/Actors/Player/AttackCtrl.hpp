#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>
#include <abyss/components/Actors/base/IStateCallback.hpp>
#include <abyss/components/Actors/Player/ChargeCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Player
{
    class AttackCtrl : 
        public IComponent,
        public ILastUpdate,
        public IStateCallback
    {
    public:
        AttackCtrl(IActor* pActor);

        void reset();
        bool isAttacking() const;

        void onStart() override;
        void onLastUpdate() override;
        void onStateStart() override;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
    private:
        void startAttack();
    private:
        IActor* m_pActor = nullptr;
        TimerEx m_timer;

        Ref<Body> m_body;
        Ref<ChargeCtrl> m_charge;

        bool m_isActive;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::AttackCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate,
            Actor::IStateCallback
        >;
    };
}